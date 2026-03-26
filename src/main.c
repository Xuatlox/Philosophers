/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:44:16 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/26 15:42:32 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_prog			prog;
	int				i;
	pthread_t		monitor;

	if (ac != 5 && ac != 6)
		return (end_prog("only 4-5 arguments allowed\n", NULL, 0, 0));
	if (prog_init(av, &prog))
		return (1);
	if (pthread_create(&monitor, NULL, monitor_routine, &prog))
		return (end_prog("monitor thread init error\n", &prog, 6, prog.nb_philo));
	i = -1;
	pthread_join(monitor, NULL);
	while (++i < prog.nb_philo)
		pthread_join(prog.philos[i].pid, NULL);
	return (end_prog(NULL, &prog, 5, prog.nb_philo));
}
