/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:47:37 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/26 17:40:24 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	display_info("has taken a fork", philo);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->is_eating);
	display_info("is eating", philo);
	pass_time(philo->eat_time, philo);
	++philo->meals;
	philo->last_meal = get_msec(philo->init);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->is_eating);
}

void	*philo_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 1)
		usleep(250);
	if (philo->r_fork == philo->l_fork)
		display_info("has taken a fork", philo);
	else
	{
		pthread_mutex_lock(philo->death);
		while (!*philo->dead)
		{
			pthread_mutex_unlock(philo->death);
			eat(philo);
			display_info("is sleeping", philo);
			pass_time(philo->sleep_time, philo);
			display_info("is thinking", philo);
			pthread_mutex_lock(philo->death);
		}
		pthread_mutex_unlock(philo->death);
	}
	return (NULL);
}
