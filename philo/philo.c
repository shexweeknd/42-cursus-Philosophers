/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:18:47 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/09 15:18:13 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*generate_forks(int p_nbr)
{
	pthread_mutex_t	*result;
	int				index;

	if (p_nbr < 0)
		return (NULL);
	result = malloc(sizeof(pthread_mutex_t) * p_nbr);
	if (!result)
		return (printf("Failed to malloc the fork mutex...\n"), NULL);
	index = 0;
	while (index < p_nbr)
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

	result = (t_data *)malloc(sizeof(t_data));
	if (!result)
		return (NULL);
	result->p_nbr = ft_atol(argv[1]);
	result->ttd = ft_atol(argv[2]);
	result->tte = ft_atol(argv[3]);
	result->tts = ft_atol(argv[4]);
	result->is_died = 0;
	result->forks = generate_forks(result->p_nbr);
	if (!(result->forks))
		return (free(result), NULL);
	if (pthread_mutex_init(&(result->printf_mutex), NULL) < 0
		|| pthread_mutex_init(&(result->data_mutex), NULL) < 0)
		return (printf("Failed to init data and pf mutexes ...\n"),
			free(result), NULL);
	if (argv[5])
		result->etf = ft_atol(argv[5]);
	else
		result->etf = 0;
	if (!is_valid_data(result) || result->etf < 0)
		return (free(result->forks), free(result),
			printf("\nError...\nProvide correct input values.\n"), NULL);
	return (result);
}

t_philo	*init_p(char **argv)
{
	t_philo	*result;
	t_data	*data;
	int		index;

	data = init_data(argv);
	if (!data)
		return (NULL);
	result = malloc(sizeof(t_philo) * (data->p_nbr));
	if (!result)
		return (free(data), NULL);
	index = 0;
	while (index < data->p_nbr)
	{
		result[index].id = index + 1;
		result[index].pos = index;
		result[index].left_fork = (index + 1) % data->p_nbr;
		result[index].right_fork = index;
		result[index].data = data;
		result[index].eating_numbers = 0;
		result[index].is_eating = 0;
		index++;
	}
	data->p = result;
	return (result);
}

int	main(int argc, char **argv)
{
	t_philo	*p_array;
	int		index;

	if (!(argc == 5 || argc == 6))
		return (printf("\nError...\n"),
			printf("\nThe syntax is ./philo [philos_nbr] [time_to_die]"),
			printf(" [time_to_eat] [time_to_sleep] [number_of_eat]\n"),
			printf("NB: [number_of_eat] is optionnal.\n"), 1);
	p_array = init_p(argv);
	if (!p_array)
		return (1);
	init_starting(p_array, ft_atol(argv[1]));
	if (!create_threads(p_array, argv))
		return (1);
	while (!is_any_dying(p_array) && !is_everyone_full(p_array))
		;
	index = 0;
	while (index < p_array->data->p_nbr)
	{
		if (pthread_join(p_array[index++].thread, NULL))
			return (printf("Failed to join the thread: %d\n", index),
				free(p_array->data), free(p_array), 1);
	}
	d_mutex_and_free(p_array);
	return (0);
}
