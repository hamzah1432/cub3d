/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halmuhis <halmuhis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:19:20 by halmuhis          #+#    #+#             */
/*   Updated: 2025/07/22 17:00:17 by halmuhis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(t_data *data, t_philosopher *philo, const char *error_msg)
{
	int	i;

	if (error_msg)
		printf("Error: %s\n", error_msg);
	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&philo[i].meal_mutex);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
	free(data);
	free(philo);
}

int	exit_with_error(const char *error_msg, t_data *data,
			t_philosopher *philos)
{
	printf("Error: %s\n", error_msg);
	if (data)
	{
		if (data->forks)
			free(data->forks);
		free(data);
	}
	if (philos)
		free(philos);
	return (0);
}

void	cleanup_mutex_init(t_data *data, t_philosopher *philosophers,
			int init_count, int cleanup_print)
{
	if (cleanup_print)
		pthread_mutex_destroy(&data->print_mutex);
	while (--init_count >= 0)
		pthread_mutex_destroy(&data->forks[init_count]);
	exit_with_error(ERR_MUTEX, data, philosophers);
}
