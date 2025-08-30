/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:02:49 by helin             #+#    #+#             */
/*   Updated: 2025/08/26 19:00:59 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct s_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;

	int				meals_eaten;
	long long		last_meal_time;
	pthread_mutex_t	state_lock;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	struct s_rules	*rules;
}					t_philo;

typedef struct s_rules
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				meals_to_eat;

	long long		start_time;
	int				stopped;

	pthread_mutex_t	stop_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
}					t_rules;

int					parse_args(int argc, char **argv, t_rules *rules);

int					init_all(t_rules *rules, t_philo **philos);
void				free_all(t_rules *rules, t_philo *philos);

int					is_simulation_stopped(t_rules *rules);
void				*philo_routine(void *arg);

int					check_philo_status(t_philo *philo, int *philos_full_count);
void				*monitor_routine(void *arg);

long				timestamp_ms(void);
void				smart_sleep(long ms, t_rules *rules);
void				print_action(t_philo *ph, char *msg);
int					ft_atoi(const char *str);
int					check_digit(char *str);

#endif