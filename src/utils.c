/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halmuhis <halmuhis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:19:50 by halmuhis          #+#    #+#             */
/*   Updated: 2025/07/21 14:58:08 by halmuhis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static int	check_death(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (1);
}

void	safe_usleep(long duration, t_philosopher *philo)
{
	long	start;
	long	current;

	start = get_time();
	while (1)
	{
		current = get_time();
		if (current - start >= duration)
			break ;
		else if (philo && check_death(philo))
			break ;
		usleep(1);
	}
}

void	print_state(t_philosopher *philo, char *state)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (check_death(philo))
	{
	pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	if (!philo->data->someone_died)
		printf("%ld %d %s\n", get_time() - philo->data->start_time,
			philo->id + 1, state);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		else
			sign = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return (result * sign);
}
