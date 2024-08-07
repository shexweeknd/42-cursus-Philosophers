/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:18:47 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/07 11:01:37 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	result->p_nbr = ft_atol(argv[1]);
	result->ttd = ft_atol(argv[2]);
	result->tte = ft_atol(argv[3]);
	result->tts = ft_atol(argv[4]);
	result->is_died = 0;
	if (pthread_mutex_init(&(result->data_mutex), NULL) < 0
		|| pthread_mutex_init(&(result->data_mutex), NULL) < 0)
		return (printf("Failed to init data and pf mutexes ...\n"),
			free(result), NULL);
	if (argv[5])
		result->etf = ft_atol(argv[5]);
	else
		result->etf = 0;
	if (!is_valid_data(result) || result->etf < 0)
		return (free(result), NULL);
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
		return (1);
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
