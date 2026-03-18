/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:10:03 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/18 18:04:06 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_prog *prog)
{
	int	i;

	i = 0;
	prog->death_end = 0;
	while (i < prog->nb_philo)
	{
		prog->philos[i].eat_time = prog->eat_time;
		prog->philos[i].sleep_time = prog->sleep_time;
		prog->philos[i].dead = &prog->death_end;
		prog->philos[i].id = i + 1;
		prog->philos[i].init = prog->initial_time;
		prog->philos[i].meals = 0;
		prog->philos[i].last_meal = prog->initial_time;
		++i;
	}
}

void	*monitor_routine(void *param)
{
	t_prog	prog;
	size_t	time;
	int		i;

	prog = *(t_prog *)param;
	while (!prog.death_end)
	{
		i = -1;
		while (++i < prog.nb_philo)
		{
			time = get_msec(prog.initial_time);
			if (prog.die_time <= prog.philos[i].last_meal - time)
			{
				printf("%ld %d died\n", time, i + 1);
				prog.death_end = 1;
			}
			if (i + 1 == prog.nb_philo)
				prog.death_end = 1;
		}
	}
	return (NULL);
}

size_t	get_msec(const size_t initial_time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (initial_time);
	return (tv.tv_usec / 1000 - initial_time);
}
