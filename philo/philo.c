/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:18:47 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/01 00:39:55 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_data(t_data *data)
{
	if (data->philos_nbr < 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (0);
	return (1);
}

t_data	*init_data(char **argv)
{
	t_data	*result;

	result = malloc(sizeof(t_data));
	if (!result)
		return (NULL);
	result->philos_nbr = ft_atol(argv[1]);
	result->time_to_die = ft_atol(argv[2]);
	result->time_to_eat = ft_atol(argv[3]);
	result->time_to_sleep = ft_atol(argv[4]);
	if (!is_valid_data(result))
		return (free(result), NULL);
	return (result);
}

t_philo	*init_philos(char **argv)
{
	t_philo	*result;
	t_data	*data;
	int		index;

	data = init_data(argv);
	if (!data)
		return (NULL);
	result = malloc(sizeof(t_philo) * data->philos_nbr);
	if (!result)
		return (free(data), NULL);
	index = 0;
	while (index < data->philos_nbr)
	{
		result[index].id = index;
		result[index].data = data;
		index++;
	}
	return (result);
}

void	*eat(void *philo)
{
	printf("philo %u is eating ...\n", ((t_philo *)philo)->id);
	sleep(1);
	return (NULL);
}

// TODO parse des arguments en long
int	main(int argc, char **argv)
{
	t_philo *philos_array;
	int index;

	if (!(argc == 4 || argc == 5))
		return (1);
	// 1er etape, init de tous les philos
	philos_array = init_philos(argv);
	// print_philos(philos_array);
	// 2em etape, create and join de tous les philos
	while (index < philos_array->data->philos_nbr)
	{
		pthread_create(&(philos_array[index].thread), NULL, eat,
			&(philos_array[index]));
		pthread_join(philos_array[index].thread, NULL);
		index++;
	}
	free(philos_array->data);
	free(philos_array);
	// 3em etape, verifier si tous les philos sont en train de manger
	return (0);
}