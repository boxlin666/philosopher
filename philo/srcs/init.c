/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:02:58 by helin             #+#    #+#             */
/*   Updated: 2025/08/31 16:34:14 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char **argv, t_rules *rules)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (printf("Usage: ./philo num_philos time_to_die "
				"time_to_eat time_to_sleep [must_eat]\n"), 1);
	i = 1;
	while (i < argc)
	{
		if (!is_valid_arg(argv[i++]))
			return (printf("Error: Invalid arguments\n"), 1);
	}
	rules->num_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->meals_to_eat = ft_atoi(argv[5]);
	else
		rules->meals_to_eat = -1;
	if (!rules->num_philos || !rules->time_to_die || !rules->time_to_eat
		|| !rules->time_to_sleep || !rules->meals_to_eat)
		return (printf("Error: Invalid arguments"), 1);
	rules->stopped = 0;
	return (0);
}

int	init_all(t_rules *rules, t_philo **philos)
{
	int	i;

	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->num_philos);
	*philos = malloc(sizeof(t_philo) * rules->num_philos);
	if (!rules->forks || !*philos)
		return (perror("malloc"), 1);
	rules->start_time = timestamp_ms();
	pthread_mutex_init(&rules->stop_lock, NULL);
	pthread_mutex_init(&rules->print_lock, NULL);
	i = 0;
	while (i < rules->num_philos)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		(*philos)[i].id = i + 1;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_meal_time = rules->start_time;
		(*philos)[i].rules = rules;
		(*philos)[i].left_fork = &rules->forks[i];
		(*philos)[i].right_fork = &rules->forks[(i + 1) % rules->num_philos];
		pthread_mutex_init(&(*philos)[i].state_lock, NULL);
		i++;
	}
	return (0);
}

void	free_all(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->num_philos)
		pthread_mutex_destroy(&rules->forks[i++]);
	pthread_mutex_destroy(&rules->print_lock);
	free(rules->forks);
	free(philos);
}
