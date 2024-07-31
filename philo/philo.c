/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:18:47 by hramaros          #+#    #+#             */
/*   Updated: 2024/07/31 23:08:23 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(unsigned int philo_numbers, unsigned int time_to_eat)
{
	unsigned int	i;
	t_philo			*result;

	result = malloc(sizeof(t_philo) * philo_numbers);
	if (!result)
		return (NULL);
	i = 0;
	while (i < philo_numbers)
	{
		result[i].id = i;
		result[i].time_to_eat = time_to_eat;
		i++;
	}
	return (result);
}

void	print_philos(t_philo *philos, int philos_nbr)
{
	int	index;

	if (!philos)
	{
		printf("No philos was created !\n");
		return ;
	}
	index = 0;
	while (index < philos_nbr)
	{
		printf("philos id: %u has %u of time_to_eat\n", philos[index].id,
			philos[index].time_to_eat);
		index++;
	}
}

void	*philo_eating(void *philo)
{
	printf("philo: %u is eating\n", ((t_philo *)philo)->id);
	sleep(((t_philo *)philo)->time_to_eat);
	return (NULL);
}

int	main(void)
{
	int philo_numbers;
	int time_to_eat;
	int index;
	t_philo *philos_array;

	philo_numbers = 5;
	time_to_eat = 1;
	// 1er etape, init de tous les philos
	philos_array = init_philos(philo_numbers, time_to_eat);
	// print_philos(philos_array, philo_numbers);
	// 2em etape, create and join de tous les philos
	index = 0;
	while (index < philo_numbers)
	{
		pthread_create(&(philos_array[index].thread), NULL, philo_eating,
			&(philos_array[index]));
		pthread_join(philos_array[index].thread, NULL);
		index++;
	}
	free(philos_array);
	// 3em etape, verifier si tous les philos sont en train de manger
	return (0);
}