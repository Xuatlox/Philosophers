/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:38:44 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/30 15:12:57 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philos_init(t_prog *prog)
{
	int	i;
	size_t	time;

	i = 0;
	time = get_msec(0);
	prog->initial_time = time;
	prog->death_end = 0;
	while (i < prog->nb_philo)
	{
		prog->philos[i].eat_time = prog->eat_time;
		prog->philos[i].sleep_time = prog->sleep_time;
		prog->philos[i].death_time = prog->die_time;
		prog->philos[i].dead = &prog->death_end;
		prog->philos[i].id = i + 1;
		prog->philos[i].init = prog->initial_time;
		prog->philos[i].meals = 0;
		prog->philos[i].last_meal = 0;
		prog->philos[i].write = &prog->write;
		prog->philos[i].death = &prog->death;
		if (pthread_mutex_init(&prog->philos[i].is_eating, NULL))
			return (end_prog("check mutex init error\n", prog, 5, i));
		++i;
	}
	return (0);
}

static int	forks_init(t_prog *prog)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&prog->write, NULL))
		return (end_prog("write mutex init error\n", prog, 1, 0));
	if (pthread_mutex_init(&prog->death, NULL))
		return (end_prog("death mutex init error\n", prog, 2, 0));
	prog->forks = malloc((prog->nb_philo + 1) * sizeof(pthread_mutex_t));
	if (!prog->forks)
		return (end_prog("forks malloc() error\n", prog, 3, 0));
	while (i < prog->nb_philo)
	{
		if (pthread_mutex_init(&prog->forks[i], NULL))
			return (end_prog("forks member init error\n", prog, 4, i));
		if (i == 0)
			prog->philos[prog->nb_philo - 1].r_fork = &prog->forks[i];
		else
			prog->philos[i - 1].r_fork = &prog->forks[i];
		prog->philos[i].l_fork = &prog->forks[i];
		++i;
	}
	return (0);
}

int	prog_init(char **av, t_prog *prog)
{
	int		i;

	prog->nb_philo = ft_atoi(av[1]);
	prog->die_time = ft_atoi(av[2]);
	prog->eat_time = ft_atoi(av[3]);
	prog->sleep_time = ft_atoi(av[4]);
	prog->turns = -1;
	if (av[5])
		prog->turns = ft_atoi(av[5]);
	if (prog->nb_philo < 1 || prog->die_time < 1 || prog->sleep_time < 1
		|| prog->eat_time < 1 || prog->turns < -1)
		return (end_prog("invalid argument\n", prog, 0, 0));
	prog->philos = malloc((prog->nb_philo + 1) * sizeof(t_philo));
	if (!prog->philos)
		return (end_prog("philo malloc error\n", prog, 0, 0));
	if (forks_init(prog))
		return (1);
	if (philos_init(prog))
		return (1);
	i = -1;
	while (++i < prog->nb_philo)
		if (pthread_create(&prog->philos[i].pid, NULL, philo_routine, &prog->philos[i]))
			return (end_prog("threads init error\n", prog, 6, i));
	return (0);
}
