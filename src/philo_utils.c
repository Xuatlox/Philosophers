/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:10:03 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/26 17:02:21 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_msec(const size_t initial_time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		write(STDERR_FILENO, "gettimeofday() error\n", 22);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - initial_time);
}

void	display_info(char *info, t_philo *philo)
{
	size_t	time;

	if (!philo)
		return ;
	pthread_mutex_lock(philo->write);
	time = get_msec(philo->init);
	printf("\033[0;32m%ld | %d %s\033[0m\n", time, philo->id, info);
	pthread_mutex_unlock(philo->write);
}

void	pass_time(const size_t ms, t_philo *philo)
{
	size_t			start;
	size_t			actual;

	if (!philo)
		return ;
	start = get_msec(0);
	actual = 0;
	pthread_mutex_lock(philo->death);
	while (actual < ms && !*philo->dead)
	{
		pthread_mutex_unlock(philo->death);
		actual = get_msec(start);
		pthread_mutex_lock(philo->death);
	}
	pthread_mutex_unlock(philo->death);
}
