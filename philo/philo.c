/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:18:47 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/05 14:19:54 by hramaros         ###   ########.fr       */
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
	if (pthread_mutex_init(&(result->data_mutex), NULL) < 0
		|| pthread_mutex_init(&(result->data_mutex), NULL) < 0)
		return (printf("Failed to init data and pf mutexes ...\n"),
			free(result), NULL);
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
	result = malloc(sizeof(t_philo) * (data->philos_nbr));
	if (!result)
		return (free(data), NULL);
	index = 0;
	while (index < data->philos_nbr)
	{
		result[index].id = index + 1;
		result[index].pos = index;
		result[index].left_fork = (index + 1) % data->philos_nbr;
		result[index].right_fork = index;
		result[index].data = data;
		result[index].eating_numbers = 0;
		index++;
	}
	data->philos = result;
	return (result);
}

int	is_any_dying(t_philo *philos)
{
	int	index;
	int	philo_numbers;

	while (get_ms() < philos->data->start_ms)
		;
	philo_numbers = philos->data->philos_nbr;
	index = 0;
	while (index < philo_numbers)
	{
		if ((get_ms()
				- philos[index].last_eat) >= (unsigned long)(philos[index].data->time_to_die))
		{
			pthread_mutex_lock(&(philos[index].data->data_mutex));
			philos[index].data->is_died = 1;
			pthread_mutex_unlock(&(philos[index].data->data_mutex));
			return (1);
		}
		index++;
	}
	return (0);
}

void	init_starting(t_philo *philos_array, long philos_nbr)
{
	int				index;
	unsigned long	time_ms;
	int				decal;

	if (philos_nbr < 5)
		decal = 100;
	else
		decal = 200;
	index = 0;
	time_ms = get_ms() + decal;
	philos_array->data->start_ms = time_ms;
	while (index < philos_nbr)
		philos_array[index++].last_eat = time_ms;
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
	init_starting(philos_array, ft_atol(argv[1]));
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
	// TODO destroy mutexes
	free(philos_array->data->forks);
	free(philos_array->data);
	free(philos_array);
	return (0);
}
