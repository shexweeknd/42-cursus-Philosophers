/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:55:21 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/01 00:30:33 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philos(t_philo *philo)
{
	int	index;

	index = 0;
	while (index < philo->data->philos_nbr)
	{
		printf("philo : %u has data %p\n", philo[index].id, philo[index].data);
		index++;
	}
}
