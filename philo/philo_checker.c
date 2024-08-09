/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:38:33 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/09 15:05:48 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_data(t_data *data)
{
	if (data->p_nbr <= 0 || data->ttd <= 0 || data->tte <= 0 || data->tts <= 0)
		return (0);
	return (1);
}

int	is_any_dying(t_philo *p)
{
	int	index;

	while (get_ms() < p->data->start_ms)
		;
	index = 0;
	while (index < p->data->p_nbr)
	{
		pthread_mutex_lock(&p[index].data->data_mutex);
		if (!p[index].is_eating && (get_ms()
				- p[index].last_eat) >= (unsigned long)(p[index].data->ttd))
		{
			p[index].data->is_died = 1;
			pthread_mutex_lock(&(p[index].data->printf_mutex));
			printf("%lu %i died\n", get_ms() - p[index].data->start_ms,
				p[index].id);
			pthread_mutex_unlock(&(p[index].data->printf_mutex));
			pthread_mutex_unlock(&(p[index].data->data_mutex));
			return (1);
		}
		pthread_mutex_unlock(&p[index].data->data_mutex);
		index++;
	}
	return (usleep(50), 0);
}

int	is_everyone_full(t_philo *p)
{
	int	index;
	int	philo_numbers;
	int	occ;

	while (get_ms() < p->data->start_ms)
		;
	philo_numbers = p->data->p_nbr;
	occ = 0;
	index = 0;
	while (index < philo_numbers)
	{
		if (p->data->etf > 0 && (get_eat_numbers(&p[index]) >= p->data->etf))
			occ++;
		index++;
	}
	if (occ == philo_numbers)
	{
		pthread_mutex_lock(&p->data->data_mutex);
		p->data->is_full = 1;
		pthread_mutex_unlock(&p->data->data_mutex);
		return (1);
	}
	return (usleep(50), 0);
}
