/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:45:15 by helin             #+#    #+#             */
/*   Updated: 2025/08/31 20:01:56 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <limits.h>

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

void	error_exit(const char *message)
{
	printf("Error: %s\n", message);
	exit(1);
}

long	timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
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

int	is_valid_arg(char *str)
{
	long long	nbr;
	int			i;

	if (!str || !*str)
		return (0);
	i = 0;
	nbr = 0;
	if (str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		if (nbr > INT_MAX)
			return (0);
		i++;
	}
	if (str[i] != '\0')
		return (0);
	if (nbr == 0)
		return (0);
	return (1);
}
