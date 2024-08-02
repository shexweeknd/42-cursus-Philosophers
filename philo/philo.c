/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:18:47 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/02 11:51:29 by hramaros         ###   ########.fr       */
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

	if (ft_atol(argv[1]) < 0)
		return (NULL);
	result = malloc(sizeof(pthread_mutex_t) * (ft_atol(argv[1]) + 1));
	if (!result)
		return (printf("Failed to malloc the fork mutex...\n"), NULL);
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
		index++;
	}
	data->philos = result;
	return (result);
}

void	take_fork_left(t_philo *philo)
{
	pthread_mutex_lock(&(((philo->data->forks)[(philo->pos + 1)
				% (philo->data->philos_nbr)])));
	printf("philo %i has taken fork number :%i\n", philo->id, (philo->pos + 1)
		% (philo->data->philos_nbr));
}

void	take_fork_right(t_philo *philo)
{
	pthread_mutex_lock(&((philo->data->forks)[philo->pos]));
	printf("philo %i has taken fork number :%i\n", philo->id, philo->pos);
}

void	leave_fork_left(t_philo *philo)
{
	pthread_mutex_unlock(&((philo->data->forks)[(philo->pos + 1)
			% (philo->data->philos_nbr)]));
}

void	leave_fork_right(t_philo *philo)
{
	pthread_mutex_unlock(&((philo->data->forks)[philo->pos]));
}

void	do_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		take_fork_right(philo);
		take_fork_left(philo);
	}
	else
	{
		take_fork_left(philo);
		take_fork_right(philo);
	}
	printf("philo %i is eating ...\n", philo->id);
	if (philo->id % 2 == 0)
	{
		leave_fork_left(philo);
		leave_fork_right(philo);
	}
	else
	{
		leave_fork_right(philo);
		leave_fork_left(philo);
	}
	philo->eating_numbers += 1;
}

void	do_sleep(t_philo *philo)
{
	printf("philo %i is sleeping ...\n", philo->id);
}

void	do_think(t_philo *philo)
{
	printf("philo %i is thinking ...\n", philo->id);
}

void	*simule(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->is_died)
	{
		do_eat(philo);
		usleep((philo)->data->time_to_eat);
		do_sleep(philo);
		usleep((philo)->data->time_to_sleep);
		do_think(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo	*philos_array;
	int		index;

	if (!(argc == 5 || argc == 6))
		return (1);
	// 1er etape, init de tous les philos
	philos_array = init_philos(argv);
	if (!philos_array)
		return (1);
	// print_philos(philos_array);
	// print_forks(philos_array);
	// 2em etape, create and join de tous les philos
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
	// TODO verifier si un philo doit mourrir ou non
	while (1)
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
	// 3em etape, verifier si tous les philos sont en train de manger
	return (0);
}
