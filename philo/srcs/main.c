/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:00:10 by helin             #+#    #+#             */
/*   Updated: 2025/08/26 18:28:05 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*philos;
	pthread_t	monitor;
	int		i;

	if (parse_args(argc, argv, &rules))
		return (1);
	if (init_all(&rules, &philos))
		return (1);
	i = 0;
	while (i < rules.num_philos)
	{
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, philos);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < rules.num_philos)
		pthread_join(philos[i++].thread, NULL);
	free_all(&rules, philos);
}
