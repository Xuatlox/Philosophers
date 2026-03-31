/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:44:31 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/31 16:45:16 by ansimonn         ###   ########.fr       */
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
	pthread_mutex_t	*write;
	pthread_mutex_t	is_eating;
	pthread_mutex_t	*death;
	int				id;
	int				*dead;
	int				eat_time;
	int				sleep_time;
	int				death_time;
	int				meals;
	size_t			last_meal;
	size_t			init;
}	t_philo;

typedef struct s_prog
{
	int				nb_philo;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				turns;
	int				death_end;
	size_t			initial_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	death;
	t_philo			*philos;
}	t_prog;

int		ft_atoi(const char *nptr);
int		prog_init(char **av, t_prog *prog);
size_t	ft_strlen(const char *s);
void	*monitor_routine(void *param);
size_t	get_msec(size_t initial_time);
void	display_info(char *info, t_philo *philo);
void	end_prog(const char *message, t_prog *prog, int free_code, int last_el);
void	pass_time(size_t ms, t_philo *philo);
void	*philo_routine(void *param);

#endif
