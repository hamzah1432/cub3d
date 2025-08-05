/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vaildate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halmuhis <halmuhis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:44:43 by halmuhis          #+#    #+#             */
/*   Updated: 2025/07/22 15:08:29 by halmuhis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_valid_number(char *str)
{
	long	num;
	int		i;

	i = 0;
	num = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		num = (num * 10) + (str[i] - '0');
		if (num > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	validate_input(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			printf("Error: invalid number format\n");
			return (0);
		}
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Error: numbers must be positive\n");
			return (0);
		}
		i++;
	}
	return (1);
}
