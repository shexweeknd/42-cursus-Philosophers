/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:53:53 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/05 16:58:17 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_starting(t_philo *p_array, long p_nbr)
{
	int				index;
	unsigned long	time_ms;
	int				decal;

	if (p_nbr < 5)
		decal = 100;
	else
		decal = 200;
	index = 0;
	time_ms = get_ms() + decal;
	p_array->data->start_ms = time_ms;
	while (index < p_nbr)
		p_array[index++].last_eat = time_ms;
}

int	create_threads(t_philo *p_array, char **argv)
{
	int	index;

	index = -1;
	while (++index < ft_atol(argv[1]))
	{
		if (pthread_create(&(p_array[index].thread), NULL, simule,
				&(p_array[index])))
			return (printf("Failed to create the thread: %d\n", index),
				free(p_array->data), free(p_array), 0);
	}
	return (1);
}
