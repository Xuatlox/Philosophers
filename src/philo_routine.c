/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:47:37 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/30 17:04:19 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->death);
	if (!*philo->dead)
		display_info("has taken a fork", philo);
	pthread_mutex_unlock(philo->death);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->death);
	if (!*philo->dead)
		display_info("is eating", philo);
	pthread_mutex_unlock(philo->death);
	pthread_mutex_lock(&philo->is_eating);
	++philo->meals;
	philo->last_meal = get_msec(philo->init);
	pthread_mutex_unlock(&philo->is_eating);
	pass_time(philo->eat_time, philo);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	if (!*philo->dead)
		display_info("is sleeping", philo);
	pthread_mutex_unlock(philo->death);
	pass_time(philo->sleep_time, philo);
}

static void philo_think(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	if (!*philo->dead)
		display_info("is thinking", philo);
	pthread_mutex_unlock(philo->death);
}

void	*philo_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 1)
		usleep(1);
	if (philo->r_fork == philo->l_fork)
		display_info("has taken a fork", philo);
	else
	{
		pthread_mutex_lock(philo->death);
		while (!*philo->dead)
		{
			pthread_mutex_unlock(philo->death);
			philo_eat(philo);
			philo_sleep(philo);
			philo_think(philo);
			pthread_mutex_lock(philo->death);
		}
		pthread_mutex_unlock(philo->death);
	}
	return (NULL);
}
