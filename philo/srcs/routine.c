/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:44:58 by helin             #+#    #+#             */
/*   Updated: 2025/08/29 18:45:32 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	philo = (t_philo *)arg;
	
	// Define the order of forks to pick up to prevent deadlock.
	// Odd-numbered philos pick left then right.
	// Even-numbered philos pick right then left.
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
	
	// Stagger the start of even-numbered philosophers to improve fairness.
	if (philo->id % 2 == 0)
		usleep(500);

	while (!is_simulation_stopped(philo->rules))
	{
		// A single philosopher can't eat and will die.
		// We handle this by picking up the fork and waiting.
		// The monitor thread will handle the death announcement.
		if (philo->rules->num_philos == 1)
		{
			pthread_mutex_lock(first_fork);
			print_action(philo, "has taken a fork");
			// Wait until death, preventing the loop from spinning.
			smart_sleep(philo->rules->time_to_die * 2, philo->rules);
			pthread_mutex_unlock(first_fork);
			break ; // Exit the loop after handling the single philo case.
		}

		// === Eating Phase ===
		

		pthread_mutex_lock(first_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(second_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->state_lock);
		
		philo->last_meal_time = timestamp_ms();
		philo->meals_eaten++;
		print_action(philo, "is eating");
		pthread_mutex_unlock(&philo->state_lock);
		
		smart_sleep(philo->rules->time_to_eat, philo->rules);
		
		// Unlock forks in the reverse order of locking (good practice).
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		
		// === Sleeping and Thinking Phase ===
		if (is_simulation_stopped(philo->rules))
			break;
		print_action(philo, "is sleeping");
		smart_sleep(philo->rules->time_to_sleep, philo->rules);
		
		if (is_simulation_stopped(philo->rules))
			break;
		print_action(philo, "is thinking");
		// A tiny sleep here can sometimes improve fairness for other philos.
		usleep(1000); 
	}
	return (NULL);
}
