/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:18:47 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/03 05:04:12 by hramaros         ###   ########.fr       */
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

pthread_mutex_t	*generate_forks(char **argv)
{
	pthread_mutex_t	*result;
	int				index;

	if (ft_atol(argv[1]) < 0)
		return (NULL);
	result = malloc(sizeof(pthread_mutex_t) * (ft_atol(argv[1]) + 1));
	if (!result)
		return (printf("Failed to malloc the fork mutex...\n"), NULL);
	index = 0;
	while (index < ft_atol(argv[1]))
	{
		if (pthread_mutex_init(&(result[index]), NULL) < 0)
			return (printf("Failed to init fork mutex...\n"), free(result),
				NULL);
		index++;
	}
	return (result);
}

t_data	*init_data(char **argv)
{
	t_data	*result;

	result = malloc(sizeof(t_data));
	if (!result)
		return (NULL);
	result->forks = generate_forks(argv);
	if (!result->forks)
		return (NULL);
	result->philos_nbr = ft_atol(argv[1]);
	result->time_to_die = ft_atol(argv[2]);
	result->time_to_eat = ft_atol(argv[3]);
	result->time_to_sleep = ft_atol(argv[4]);
	result->is_died = 0;
	if (pthread_mutex_init(&(result->data_mutex), NULL) < 0)
		return (printf("Failed to init data mutex...\n"), free(result), NULL);
	if (argv[5])
		result->eat_to_full = ft_atol(argv[5]);
	else
		result->eat_to_full = -1;
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
	result = malloc(sizeof(t_philo) * (data->philos_nbr + 1));
	if (!result)
		return (free(data), NULL);
	index = 0;
	while (index < data->philos_nbr)
	{
		result[index].id = index + 1;
		result[index].pos = index;
		result[index].data = data;
		result[index].eating_numbers = 0;
		result[index].last_eat = get_ms();
		if (pthread_mutex_init(&(result[index].philo_mutex), NULL) < 0)
			return (printf("Failed to init philo %d mutex...\n", index),
				free(result->data), free(result), NULL);
		index++;
	}
	data->philos = result;
	return (result);
}

int	is_any_dying(t_philo *philos)
{
	int	index;
	int	philo_numbers;

	philo_numbers = philos->data->philos_nbr;
	index = 0;
	while (index < philo_numbers)
	{
		pthread_mutex_lock(&(philos[index].data->data_mutex));
		if ((get_ms()
				- philos[index].last_eat) > (unsigned long)(philos[index].data->time_to_die))
		{
			philos[index].data->is_died = 1;
			pthread_mutex_unlock(&(philos[index].data->data_mutex));
			return (1);
		}
		pthread_mutex_unlock(&(philos[index].data->data_mutex));
		index++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philos_array;
	int		index;

	if (!(argc == 5 || argc == 6))
		return (1);
	philos_array = init_philos(argv);
	if (!philos_array)
		return (1);
	philos_array->data->start_ms = get_ms();
	philos_array->data->start_us = get_us();
	index = 0;
	while (index < ft_atol(argv[1]))
	{
		if (pthread_create(&(philos_array[index].thread), NULL, simule,
				&(philos_array[index])) != 0)
		{
			printf("Failed to create the thread: %d\n", index);
			return (free(philos_array->data), free(philos_array), 1);
		};
		index++;
	}
	while (!is_any_dying(philos_array))
		;
	index = 0;
	while (index < philos_array->data->philos_nbr)
	{
		if (pthread_join(philos_array[index].thread, NULL) != 0)
		{
			printf("Failed to join the thread: %d\n", index);
			return (free(philos_array->data), free(philos_array), 1);
		};
		index++;
	}
	free(philos_array->data->forks);
	free(philos_array->data);
	free(philos_array);
	return (0);
}
