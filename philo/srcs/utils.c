/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:45:15 by helin             #+#    #+#             */
/*   Updated: 2025/08/26 21:23:43 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return ((int)(res * sign));
}

long	timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void	smart_sleep(long ms, t_rules *rules)
{
	long	start;

	start = timestamp_ms();

	while (!is_simulation_stopped(rules) && (timestamp_ms() - start) < ms)
		usleep(500);
}

void	print_action(t_philo *ph, char *msg)
{
	pthread_mutex_lock(&ph->rules->print_lock);
	if (!is_simulation_stopped(ph->rules))
		printf("%lld %d %s\n", timestamp_ms() - ph->rules->start_time, ph->id, msg);
	pthread_mutex_unlock(&ph->rules->print_lock);
}

int	check_digit(char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}
