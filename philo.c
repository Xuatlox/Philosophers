/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:44:16 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/16 16:41:24 by ansimonn         ###   ########.fr       */
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
	i = -1;
	if (prog->philos)
	{
		while (++i < prog->nb_philo)
			pthread_join(prog->philos[i].pid, NULL);
		free(prog->philos);
	}
	if (prog->forks)
	{
		i = -1;
		while (++i < prog->nb_philo)
			pthread_mutex_destroy(&prog->forks[i]);
		free(prog->forks);
	}
	exit(EXIT_SUCCESS);
}

void	*philo_routine(void *param)
{
	t_philo			philo;
	struct timeval	tv;

	tv.tv_usec = philo.init;
	philo = *(t_philo *)param;
	while (*philo.dead == 0 && philo.turns != 0)
	{
		pthread_mutex_lock(philo.l_fork);
		gettimeofday(&tv, NULL);
		printf("%ld %d has taken a fork\n", tv.tv_usec - philo.init, philo.id);
		pthread_mutex_lock(philo.r_fork);
		gettimeofday(&tv, NULL);
		printf("%ld %d is eating\n", tv.tv_usec - philo.init, philo.id);
		usleep(philo.eat_time);
		pthread_mutex_unlock(philo.l_fork);
		pthread_mutex_unlock(philo.r_fork);
		gettimeofday(&tv, NULL);
		printf("%ld %d is sleeping\n", tv.tv_usec - philo.init, philo.id);
		usleep(philo.sleep_time);
		gettimeofday(&tv, NULL);
		printf("%ld %d is thinking\n", tv.tv_usec - philo.init, philo.id);
		if (philo.turns != -1)
			--philo.turns;
	}
	return (NULL);
}

static void	fork_init(t_prog *prog)
{
	int	i;

	i = 0;
	prog->forks = ft_calloc(prog->nb_philo + 1, sizeof(pthread_mutex_t));
	if (!prog->forks)
		error("forks could not be allocated.", prog);
	while (i < prog->nb_philo)
	{
		if (pthread_mutex_init(&prog->forks[i], NULL))
			error("forks member could not be initialized.", prog);
		if (i == 0)
			prog->philos[prog->nb_philo - 1].r_fork = &prog->forks[i];
		else
			prog->philos[i - 1].r_fork = &prog->forks[i];
		prog->philos[i].l_fork = &prog->forks[i];
		++i;
	}
}

static void prog_init(char **av, t_prog *prog)
{
	int	i;
	struct timeval	tv;

	prog->nb_philo = ft_atoi(av[1]);
	prog->die_time = ft_atoi(av[2]);
	prog->eat_time = ft_atoi(av[3]);
	prog->sleep_time = ft_atoi(av[4]);
	prog->turns = -1;
	if (av[5])
		prog->turns = ft_atoi(av[5]);
	prog->philos = ft_calloc(prog->nb_philo + 1, sizeof(t_philo));
	if (!prog->philos)
		error("philo could not be allocated.", prog);
	fork_init(prog);
	if (gettimeofday(&tv, NULL))
		error("gettimeofday error", prog);
	prog->initial_time = tv.tv_usec;
	philo_init(prog);
	i = -1;
	while (++i < prog->nb_philo)
		if (pthread_create(&prog->philos[i].pid, NULL, philo_routine, &prog->philos[i]))
			error("threads creation error", prog);
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
	i = -1;
	while (++i < prog.nb_philo)
		pthread_join(prog.philos->pid, NULL);
	i = -1;
	while (++i < prog.nb_philo)
		pthread_mutex_destroy(&prog.forks[i]);
	free(prog.philos);
	free(prog.forks);
	return (0);
}
