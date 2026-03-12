/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:44:16 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/12 18:56:15 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void error(const char *message, t_prog *prog)
{
	int	i;

	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	if (!prog)
		exit(EXIT_SUCCESS);
	i = 0;
	if (prog->philos)
	{
		while (i < prog->nb_philo)
		{
			pthread_join(prog->philos[i].pid, NULL);
			++i;
		}
		free(prog->philos);
	}
	if (prog->forks)
	{
		i = 0;
		while (prog->forks[i])
		{
			pthread_mutex_destroy(prog->forks[i]);
			free(prog->forks[i]);
			++i;
		}
		free(prog->forks);
	}
	exit(EXIT_SUCCESS);
}

void	*philo_routine(void *param)
{
	t_philo	philo;

	philo = *(t_philo *)param;
	while (!philo.dead)
	{
		pthread_mutex_lock(philo.l_fork);
		printf("%d has taken a fork\n", philo.id);
		pthread_mutex_lock(philo.r_fork);
		printf("%d is eating\n", philo.id);
		usleep(philo.eat_time);
		pthread_mutex_unlock(philo.l_fork);
		pthread_mutex_unlock(philo.r_fork);
		printf("%d is sleeping\n", philo.id);
		usleep(philo.sleep_time);
		printf("%d is thinking\n", philo.id);
	}
	return (NULL);
}

static void	fork_init(t_prog *prog)
{
	int	i;

	i = 0;
	prog->forks = ft_calloc(prog->nb_philo + 1, sizeof(pthread_mutex_t *));
	if (!prog->forks)
		error("forks could not be allocated.", prog);
	while (i < prog->nb_philo)
	{
		prog->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!prog->forks[i])
			error("forks member could not be allocated.", prog);
		if (pthread_mutex_init(prog->forks[i], NULL))
			error("forks member could not be initialized.", prog);
		if (i == 0)
			prog->philos[prog->nb_philo - 1].l_fork = &(*prog->forks)[i];
		else
			prog->philos[i - 1].l_fork = &(*prog->forks)[i];
		prog->philos[i].r_fork = &(*prog->forks)[i];
		++i;
	}
}

static void prog_init(char **av, t_prog *prog)
{
	int	i;

	prog->nb_philo = ft_atoi(av[1]);
	prog->die_time = ft_atoi(av[2]);
	prog->eat_time = ft_atoi(av[3]);
	prog->sleep_time = ft_atoi(av[4]);
	if (av[5])
		prog->turns = ft_atoi(av[5]);
	else
		prog->turns = -1;
	prog->philos = ft_calloc(prog->nb_philo + 1, sizeof(t_philo));
	if (!prog->philos)
		error("philo could not be allocated.", prog);
	fork_init(prog);
	philo_init(prog);
	i = 0;
	while (i < prog->nb_philo)
	{
		if (pthread_create(&prog->philos[i].pid, NULL, philo_routine, &prog->philos[i]))
			error("threads creation error", prog);
		++i;
	}
	if (prog->nb_philo <= 0 || prog->die_time <= 0 || prog->eat_time <= 0
		|| prog->sleep_time <= 0 || prog->turns < -1)
		error("Invalid input", prog);
}

int	main(int ac, char **av)
{
	t_prog			prog;
	int				i;

	if (ac != 5 && ac != 6)
		error("Wrong number of arguments.", NULL);
	prog_init(av, &prog);
	i = 0;
	while (i < prog.nb_philo)
	{
		pthread_join(prog.philos->pid, NULL);
		++i;
	}
	i = 0;
	while (i < prog.nb_philo)
	{
		pthread_mutex_destroy(&(*prog.forks)[i]);
		free(&(*prog.forks)[i]);
		++i;
	}
	free(prog.philos);
	free(prog.forks);
	return (0);
}
