/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:55:21 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/02 11:53:07 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philos(t_philo *philo)
{
	int	index;

	index = 0;
	while (index < philo->data->philos_nbr)
	{
		printf("philo id: %i has position: %i", philo[index].id,
			philo[index].pos);
		index++;
	}
}
