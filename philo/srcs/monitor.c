/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:43:12 by helin             #+#    #+#             */
/*   Updated: 2025/08/31 16:52:23 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_rules	*rules;
	int		i;
	int		philos_full_count;

	philos = (t_philo *)arg;
	rules = philos[0].rules;
	while (!is_simulation_stopped(rules))
	{
		i = -1;
		philos_full_count = 0;
		while (++i < rules->num_philos)
			if (check_philo_status(&philos[i], &philos_full_count))
				break ;
		if (rules->meals_to_eat > 0 && philos_full_count == rules->num_philos)
		{
			pthread_mutex_lock(&rules->stop_lock);
			rules->stopped = 1;
			pthread_mutex_unlock(&rules->stop_lock);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}
