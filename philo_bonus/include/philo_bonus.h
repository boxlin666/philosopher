#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>

# define SEM_FORKS "/philo_forks"
# define SEM_PRINT "/philo_print"
# define SEM_STOP "/philo_stop"

struct s_rules;

typedef struct s_philo
{
    int id;
    pid_t pid;
    long last_meal_time;
    int meals_eaten; 
    pthread_mutex_t state_lock;
    struct s_rules *rules;
} t_philo;

typedef struct s_rules
{
    int num_philos;
    long long time_to_die;
    long long time_to_eat;
    long long time_to_sleep;
    int meals_to_eat;
    long long start_time;

    t_philo *philos;
    sem_t *sem_forks;
    sem_t *sem_print;
    sem_t *sem_stop;

} t_rules;

void cleanup(t_rules *rules);
void error_exit(const char *message);

int  init_rules(int argc, char **argv, t_rules *rules);
int  init_semaphores(t_rules *rules);

long ft_atol(const char *str);
void philo_routine(t_philo *philo);
long long timestamp_ms(void);
void print_action(t_philo *ph, char *msg);

#endif
