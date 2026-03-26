/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_prog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:41:43 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/26 15:42:07 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_prog(const char *message, t_prog *prog, int free_code, int last_el)
{
	if (message)
		write(STDERR_FILENO, message, ft_strlen(message));
	if (free_code > 5)
		while (--last_el >= 0)
			pthread_detach(prog->philos[last_el].pid);
	if (free_code > 5)
		last_el = prog->nb_philo;
	if (free_code > 4)
		while (--last_el >= 0)
			pthread_mutex_destroy(&prog->philos[last_el].is_eating);
	if (free_code > 4)
		last_el = prog->nb_philo;
	if (free_code > 3)
		while (--last_el >= 0)
			pthread_mutex_destroy(&prog->forks[last_el]);
	if (free_code > 3)
		free(prog->forks);
	if (free_code > 2)
		pthread_mutex_destroy(&prog->death);
	if (free_code > 1)
		pthread_mutex_destroy(&prog->write);
	if (free_code > 0)
		free(prog->philos);
	return (1);
}
