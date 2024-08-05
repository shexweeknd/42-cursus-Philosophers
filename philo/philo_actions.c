/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:26:04 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/05 17:01:30 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	do_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&(philo->data->printf_mutex));
	if (!philo->data->is_died)
		printf("%lu %i is eating\n", get_ms() - philo->data->start_ms,
			philo->id);
	pthread_mutex_unlock(&(philo->data->printf_mutex));
	pthread_mutex_lock(&(philo->data->data_mutex));
	philo->eating_numbers += 1;
	philo->last_eat = get_ms();
	pthread_mutex_unlock(&(philo->data->data_mutex));
	ft_usleep((philo)->data->tte);
	leave_forks(philo);
}

static void	do_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->printf_mutex));
	if (!philo->data->is_died)
		printf("%lu %i is sleeping\n", get_ms() - philo->data->start_ms,
			philo->id);
	pthread_mutex_unlock(&(philo->data->printf_mutex));
}

static void	do_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->printf_mutex));
	if (!philo->data->is_died)
		printf("%lu %i is thinking\n", get_ms() - philo->data->start_ms,
			philo->id);
	pthread_mutex_unlock(&(philo->data->printf_mutex));
}

void	*simule(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_ms() < philo->data->start_ms)
		;
	if (philo->id % 2)
		usleep(200);
	while (!philo->data->is_died)
	{
		do_eat(philo);
		do_sleep(philo);
		ft_usleep((philo)->data->tts);
		do_think(philo);
	}
	return (NULL);
}
