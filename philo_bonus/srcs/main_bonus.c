/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:43:48 by helin             #+#    #+#             */
/*   Updated: 2025/08/31 17:50:35 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		i;

	if (init_rules(argc, argv, &rules))
		return (1);
	if (init_semaphores(&rules))
		return (1);
	i = -1;
	rules.start_time = timestamp_ms();
	while (++i < rules.num_philos)
	{
		rules.philos[i].pid = fork();
		if (rules.philos[i].pid == -1)
			error_exit("Fork failed");
		if (rules.philos[i].pid == 0)
			philo_routine(&rules.philos[i]);
	}
	sem_wait(rules.sem_stop);
	cleanup(&rules);
}

void	cleanup(t_rules *rules)
{
	int i;
	i = -1;
	while (++i < rules->num_philos)
	{
		if (rules->philos->pid > 0)
			kill(rules->philos[i].pid, SIGKILL);
	}
	i = -1;
	while (++i < rules->num_philos)
		waitpid(-1, NULL, 0);

	sem_close(rules->sem_forks);
	sem_close(rules->sem_print);
	sem_close(rules->sem_stop);

	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_STOP);

	free(rules->philos);
}