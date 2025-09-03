/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:57:53 by helin             #+#    #+#             */
/*   Updated: 2025/09/02 21:41:24 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_routine(void *arg);

void	philo_routine(t_philo *philo)
{
	pthread_t	monitor;

	philo->last_meal_time = philo->rules->start_time;
	if (pthread_create(&monitor, NULL, &monitor_routine, philo) != 0)
		error_exit("Fail to create monitor thread", philo->rules);
	pthread_detach(monitor);
	while (1)
	{
		sem_wait(philo->rules->sem_forks);
		print_action(philo, "has taken a fork");
		sem_wait(philo->rules->sem_forks);
		print_action(philo, "has taken a fork");
		print_action(philo, "is eating");
		pthread_mutex_lock(&philo->state_lock);
		philo->last_meal_time = timestamp_ms();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->state_lock);
		usleep(philo->rules->time_to_eat * 1000);
		sem_post(philo->rules->sem_forks);
		sem_post(philo->rules->sem_forks);
		print_action(philo, "is sleeping");
		usleep(philo->rules->time_to_sleep * 1000);
		print_action(philo, "is thinking");
	}
	pthread_mutex_destroy(&philo->state_lock);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->state_lock);
		time = timestamp_ms();
		if (time - philo->last_meal_time > philo->rules->time_to_die)
		{
			print_death(philo, "died");
			sem_post(philo->rules->sem_stop);
			break ;
		}
		if (philo->rules->meals_to_eat != -1
			&& philo->meals_eaten == philo->rules->meals_to_eat)
		{
			sem_post(philo->rules->sem_stop);
			break ;
		}
		pthread_mutex_unlock(&philo->state_lock);
		usleep(1000);
	}
	return (NULL);
}

void	print_action(t_philo *ph, char *msg)
{
	sem_wait(ph->rules->sem_print);
	printf("%ld %d %s\n", timestamp_ms() - ph->rules->start_time, ph->id, msg);
	sem_post(ph->rules->sem_print);
}

void	print_death(t_philo *ph, char *msg)
{
	sem_wait(ph->rules->sem_print);
	printf("%ld %d %s\n", timestamp_ms() - ph->rules->start_time, ph->id, msg);
}
