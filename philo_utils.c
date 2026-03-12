/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:10:03 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/12 18:29:46 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_philo)
	{
		prog->philos[i].die_time = prog->die_time;
		prog->philos[i].eat_time = prog->eat_time;
		prog->philos[i].sleep_time = prog->sleep_time;
		prog->philos[i].dead = &prog->death_end;
		prog->philos[i].id = i + 1;
		++i;
	}
}
