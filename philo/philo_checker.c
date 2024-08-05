/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:38:33 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/05 16:39:30 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_data(t_data *data)
{
	if (data->p_nbr < 0 || data->ttd < 0 || data->tte < 0 || data->tts < 0)
		return (0);
	return (1);
}

int	is_any_dying(t_philo *p)
{
	int	index;
	int	philo_numbers;

	while (get_ms() < p->data->start_ms)
		;
	philo_numbers = p->data->p_nbr;
	index = 0;
	while (index < philo_numbers)
	{
		if ((get_ms()
				- p[index].last_eat) >= (unsigned long)(p[index].data->ttd))
		{
			pthread_mutex_lock(&(p[index].data->data_mutex));
			p[index].data->is_died = 1;
			pthread_mutex_unlock(&(p[index].data->data_mutex));
			pthread_mutex_lock(&(p[index].data->printf_mutex));
			printf("%lu %i died\n", get_ms() - p[index].data->start_ms,
				p[index].id);
			pthread_mutex_unlock(&(p[index].data->printf_mutex));
			return (1);
		}
		index++;
	}
	return (0);
}