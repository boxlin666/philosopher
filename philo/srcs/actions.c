/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:28:41 by helin             #+#    #+#             */
/*   Updated: 2025/08/29 18:47:46 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_simulation_stopped(t_rules *rules)
{
    int stopped;

    pthread_mutex_lock(&rules->stop_lock);
    stopped = rules->stopped;
    pthread_mutex_unlock(&rules->stop_lock);
    return (stopped);
}

int check_philo_status(t_philo *philo, int *philos_full_count)
{
    long long now;
    
    pthread_mutex_lock(&philo->state_lock);
    now = timestamp_ms();
    if(now - philo->last_meal_time > philo->rules->time_to_die)
    {
        print_action(philo, "died");
        pthread_mutex_lock(&philo->rules->stop_lock);
        philo->rules->stopped = 1;
        pthread_mutex_unlock(&philo->rules->stop_lock);

        pthread_mutex_unlock(&philo->state_lock);
        return (1);
    }
    if(philo->rules->meals_to_eat > 0 && philo->meals_eaten >= philo->rules->meals_to_eat)
        (*philos_full_count)++;
    pthread_mutex_unlock(&philo->state_lock);
    return 0;
}
