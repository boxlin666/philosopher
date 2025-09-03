/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:49:04 by helin             #+#    #+#             */
/*   Updated: 2025/09/02 21:48:18 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define SEM_FORKS "/philo_forks"
# define SEM_PRINT "/philo_print"
# define SEM_STOP "/philo_stop"

struct	s_rules;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	state_lock;
	struct s_rules	*rules;
}					t_philo;

typedef struct s_rules
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_to_eat;
	long			start_time;

	t_philo			*philos;
	sem_t			*sem_forks;
	sem_t			*sem_print;
	sem_t			*sem_stop;
	int				sems_initialized;

}					t_rules;

void				cleanup(t_rules *rules);
void				error_exit(const char *message, t_rules *rules);

int					init_rules(int argc, char **argv, t_rules *rules);
int					init_semaphores(t_rules *rules);

int					ft_atoi(const char *str);
void				philo_routine(t_philo *philo);
long				timestamp_ms(void);
void				print_action(t_philo *ph, char *msg);
void				print_death(t_philo *ph, char *msg);
int					is_valid_arg(char *str);

#endif
