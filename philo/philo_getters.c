/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_getters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:07:49 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/09 13:46:39 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_die_state(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->data_mutex);
	result = data->is_died;
	pthread_mutex_unlock(&data->data_mutex);
	return (result);
}

int	get_full_state(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->data_mutex);
	result = data->is_full;
	pthread_mutex_unlock(&data->data_mutex);
	return (result);
}

int	get_eat_numbers(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->data_mutex);
	result = philo->eating_numbers;
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (result);
}
