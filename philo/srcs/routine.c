/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:44:58 by helin             #+#    #+#             */
/*   Updated: 2025/08/31 16:48:35 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->state_lock);
	print_action(philo, "is eating");
	philo->last_meal_time = timestamp_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->state_lock);
	smart_sleep(philo->rules->time_to_eat, philo->rules);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

static void	philo_sleep_and_think(t_philo *philo)
{
	print_action(philo, "is sleeping");
	smart_sleep(philo->rules->time_to_sleep, philo->rules);
	if (is_simulation_stopped(philo->rules))
		return ;
	print_action(philo, "is thinking");
	usleep(1000);
}

static void	handle_single_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	smart_sleep(philo->rules->time_to_die * 2, philo->rules);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->rules->num_philos == 1)
	{
		handle_single_philosopher(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(500);
	while (!is_simulation_stopped(philo->rules))
	{
		philo_eat(philo);
		if (is_simulation_stopped(philo->rules))
			break ;
		philo_sleep_and_think(philo);
	}
	return (NULL);
}
