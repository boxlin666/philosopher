/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:51:36 by helin             #+#    #+#             */
/*   Updated: 2025/08/31 17:54:56 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_rules(int argc, char **argv, t_rules *rules)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (printf("Usage: ./philo number_of_philosophers time_to_die "
				"time_to_eat time_to_sleep [meals_to_eat]"), 1);
	rules->num_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->meals_to_eat = ft_atoi(argv[5]);
	else
		rules->meals_to_eat = -1;
	rules->start_time = timestamp_ms();
	rules->philos = malloc(sizeof(t_philo) * rules->num_philos);
	i = 1;
    while (i < argc)
		if (!is_valid_arg(argv[i++]))
			error_exit("Invalid argument");
    i = -1;
	while (++i < rules->num_philos)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].meals_eaten = 0;
		rules->philos[i].last_meal_time = rules->start_time;
		rules->philos[i].rules = rules;
		pthread_mutex_init(&rules->philos[i].state_lock, NULL);
	}
	return (0);
}

int	init_semaphores(t_rules *rules)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_STOP);
	rules->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0644, rules->num_philos);
	if (rules->sem_forks == SEM_FAILED)
		return (1);
	rules->sem_print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (rules->sem_print == SEM_FAILED)
	{
		sem_close(rules->sem_forks);
		sem_unlink(SEM_FORKS);
		return (1);
	}
	rules->sem_stop = sem_open(SEM_STOP, O_CREAT, 0644, 0);
	if (rules->sem_stop == SEM_FAILED)
	{
		sem_close(rules->sem_forks);
		sem_close(rules->sem_print);
		sem_unlink(SEM_FORKS);
		sem_unlink(SEM_PRINT);
		return (1);
	}
	return (0);
}
