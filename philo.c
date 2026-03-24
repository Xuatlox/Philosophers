/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:44:16 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/24 17:11:06 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(const char *message, t_prog *prog)
{
	int	i;

	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	if (!prog)
		return (1);
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
	return (1);
}

void	*philo_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (!*philo->dead)
	{
		if (philo->id % 2 == 0)
			pthread_mutex_lock(philo->l_fork);
		else
			pthread_mutex_lock(philo->r_fork);
		display_info("has taken a fork", philo);
		if (philo->r_fork == philo->l_fork)
			break ;
		if (philo->id % 2 == 0)
			pthread_mutex_lock(philo->r_fork);
		else
			pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(&philo->is_eating);
		display_info("is eating", philo);
		usleep(philo->eat_time * 1000);
		++philo->meals;
		philo->last_meal = get_msec(philo->init);
		pthread_mutex_unlock(&philo->is_eating);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		display_info("is sleeping", philo);
		usleep(philo->sleep_time * 1000);
		display_info("is thinking", philo);
	}
	return (NULL);
}

static int	fork_init(t_prog *prog)
{
	int	i;

	i = 0;
	prog->forks = ft_calloc(prog->nb_philo + 1, sizeof(pthread_mutex_t));
	if (!prog->forks)
		return (error("forks could not be allocated.", prog));
	while (i < prog->nb_philo)
	{
		if (pthread_mutex_init(&prog->forks[i], NULL))
			return (error("forks member could not be initialized.", prog));
		if (i == 0)
			prog->philos[prog->nb_philo - 1].r_fork = &prog->forks[i];
		else
			prog->philos[i - 1].r_fork = &prog->forks[i];
		prog->philos[i].l_fork = &prog->forks[i];
		++i;
	}
	return (0);
}

static int prog_init(char **av, t_prog *prog)
{
	int		i;
	ssize_t	time;

	prog->nb_philo = ft_atoi(av[1]);
	prog->die_time = ft_atoi(av[2]);
	prog->eat_time = ft_atoi(av[3]);
	prog->sleep_time = ft_atoi(av[4]);
	prog->turns = -1;
	if (av[5])
		prog->turns = ft_atoi(av[5]);
	prog->philos = ft_calloc(prog->nb_philo + 1, sizeof(t_philo));
	if (!prog->philos)
		return (error("philo could not be allocated.", prog));
	fork_init(prog);
	time = get_msec(0);
	prog->initial_time = time;
	if (philo_init(prog))
		return (error("philos could not be initialized.", prog));
	i = -1;
	while (++i < prog->nb_philo)
		if (pthread_create(&prog->philos[i].pid, NULL, philo_routine, &prog->philos[i]))
			return (error("threads creation error", prog));
	if (prog->nb_philo <= 0 || prog->die_time <= 0 || prog->eat_time <= 0
		|| prog->sleep_time <= 0 || prog->turns < -1)
		return (error("Invalid input", prog));
	return (0);
}

int	main(int ac, char **av)
{
	t_prog			prog;
	int				i;
	pthread_t		monitor;

	if (ac != 5 && ac != 6)
	{
		error("Wrong number of arguments.", NULL);
		return (0);
	}
	if (prog_init(av, &prog))
		return (0);
	pthread_create(&monitor, NULL, monitor_routine, &prog);
	i = -1;
	pthread_join(monitor, NULL);
	while (++i < prog.nb_philo)
		pthread_join(prog.philos[i].pid, NULL);
	i = -1;
	while (++i < prog.nb_philo)
	{
		pthread_mutex_destroy(&prog.forks[i]);
		pthread_mutex_destroy(&prog.philos[i].is_eating);
	}
	free(prog.philos);
	free(prog.forks);
	return (0);
}
