/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:45:15 by helin             #+#    #+#             */
/*   Updated: 2025/08/28 20:37:57 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <limits.h>

long ft_atol(const char *str)
{
    long    result;
    int     i;

    result = 0;
    i = 0;
    // Skip any leading whitespace characters.
    while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
        i++;
    // The Philosophers project does not accept negative numbers.
    if (str[i] == '-' || str[i] == '+')
    {
        error_exit("Invalid input: signs are not allowed.");
    }
    // Convert the numeric part of the string to a long.
    while (str[i] >= '0' && str[i] <= '9')
    {
        // Simple overflow check for 10 * result + digit.
        if (result > (__LONG_MAX__ - (str[i] - '0')) / 10)
            error_exit("Invalid input: number is too large.");
        result = result * 10 + (str[i] - '0');
        i++;
    }
    // If we encounter any non-digit character after starting, it's an error.
    if (str[i] != '\0')
    {
        error_exit("Invalid input: contains non-digit characters.");
    }
    return (result);
}

long long	timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}


void	print_action(t_philo *ph, char *msg)
{
	sem_wait(ph->rules->sem_print);
	printf("%lld %d %s\n", timestamp_ms() - ph->rules->start_time, ph->id, msg);
	sem_post(ph->rules->sem_print);
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

void error_exit(const char *msg)
{
	printf("%s", msg);
	exit(1);
}