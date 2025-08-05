/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halmuhis <halmuhis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:19:32 by halmuhis          #+#    #+#             */
/*   Updated: 2025/07/22 16:55:23 by halmuhis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data **data, int argc, char **argv)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		return (exit_with_error(ERR_MALLOC, NULL, NULL));
	(*data)->num_philos = ft_atoi(argv[1]);
	(*data)->time_to_die = ft_atoi(argv[2]);
	(*data)->time_to_eat = ft_atoi(argv[3]);
	(*data)->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		(*data)->must_eat_count = ft_atoi(argv[5]);
	}
	else
	{
		(*data)->must_eat_count = -1;
	}
	(*data)->someone_died = 0;
	(*data)->forks = malloc(sizeof(pthread_mutex_t) * (*data)->num_philos);
	if (!(*data)->forks)
	{
		free(*data);
		return (exit_with_error(ERR_MALLOC, NULL, NULL));
	}
	return (1);
}

int	init_philosophers(t_philosopher **philos, t_data *data)
{
	int	i;

	*philos = malloc(sizeof(t_philosopher) * data->num_philos);
	if (!*philos)
		return (exit_with_error(ERR_MALLOC, data, NULL));
	i = -1;
	while (++i < data->num_philos)
	{
		(*philos)[i].id = i;
		(*philos)[i].times_eaten = 0;
		(*philos)[i].data = data;
		(*philos)[i].thread = 0;
		if (pthread_mutex_init(&(*philos)[i].meal_mutex, NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(*philos)[i].meal_mutex);
			return (exit_with_error(ERR_MUTEX, data, *philos));
		}
		(*philos)[i].last_meal_time = get_time();
	}
	return (1);
}

int	init_mutexes(t_data *data, t_philosopher *philosophers)
{
	int	i;
	int	init_count;

	i = -1;
	init_count = 0;
	while (++i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			cleanup_mutex_init(data, philosophers, init_count, 0);
			return (0);
		}
		init_count++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
	{
		cleanup_mutex_init(data, philosophers, init_count, 0);
		return (0);
	}
	if (pthread_mutex_init(&data->death_mutex, NULL))
	{
		cleanup_mutex_init(data, philosophers, init_count, 1);
		return (0);
	}
	return (1);
}

int	init_threads(t_data *data, t_philosopher *philosophers,
			pthread_t *monitor)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->death_mutex);
	while (++i < data->num_philos)
	{
		if (pthread_create(&philosophers[i].thread, NULL,
				philosopher_routine, &philosophers[i]))
		{
			// cleanup(data, philosophers, ERR_THREAD);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (0);
		}
	}
	if (pthread_create(monitor, NULL, monitor_routine, philosophers))
	{
		// cleanup(data, philosophers, ERR_THREAD);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (0);
	}
	data->start_time = get_time();
	pthread_mutex_unlock(&data->death_mutex);
	return (1);
}
