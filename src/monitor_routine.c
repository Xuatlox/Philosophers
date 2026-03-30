/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:44:22 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/30 16:10:48 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	proc_death(t_prog *prog, const int philo)
{
	prog->death_end = 1;
	pthread_mutex_unlock(prog->philos[philo].death);
	pthread_mutex_lock(prog->philos[philo].write);
	printf("\033[0;31m%zd %d died\033[0m\n", get_msec(prog->initial_time), philo + 1);
	pthread_mutex_unlock(prog->philos[philo].write);
}

static int check_end(t_prog *prog)
{
	size_t	time;
	int		i;
	int		end;

	i = 0;
	end = 1;
	while (i < prog->nb_philo)
	{
		pthread_mutex_lock(&prog->philos[i].is_eating);
		pthread_mutex_lock(prog->philos[i].death);
		time = get_msec(prog->initial_time);
		if ((size_t)prog->die_time <= time - prog->philos[i].last_meal
			&& !prog->death_end)
			proc_death(prog, i);
		else
			pthread_mutex_unlock(prog->philos[i].death);
		pthread_mutex_unlock(&prog->philos[i].is_eating);
		if (prog->philos[i].meals < prog->turns)
			end = 0;
		++i;
	}
	return (end);
}

void	*monitor_routine(void *param)
{
	t_prog	*prog;
	int		end;

	prog = (t_prog *)param;
	usleep(250);
	pthread_mutex_lock(&prog->death);
	while (!prog->death_end)
	{
		pthread_mutex_unlock(&prog->death);
		end = check_end(prog);
		if (end && prog->turns != -1)
		{
			pthread_mutex_lock(&prog->death);
			prog->death_end = 1;
			pthread_mutex_unlock(&prog->death);
		}
		pthread_mutex_lock(&prog->death);
	}
	pthread_mutex_unlock(&prog->death);
	return (NULL);
}
