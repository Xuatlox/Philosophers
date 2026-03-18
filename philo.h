/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:44:31 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/18 17:53:49 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		pid;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				id;
	int				*dead;
	int				eat_time;
	int				sleep_time;
	int				meals;
	size_t			last_meal;
	size_t			init;
} t_philo;

typedef struct	s_prog
{
	int				nb_philo;
	size_t			die_time;
	int				eat_time;
	int				sleep_time;
	int				turns;
	int				death_end;
	size_t			initial_time;
	pthread_mutex_t	*forks;
	t_philo			*philos;
} t_prog;

int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
void	philo_init(t_prog *prog);
void	*monitor_routine(void *param);
size_t	get_msec(size_t initial_time);

#endif
