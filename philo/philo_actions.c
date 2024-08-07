/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:26:04 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/07 14:46:00 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	do_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&(philo->data->printf_mutex));
	if (!(philo->data->is_died || philo->data->is_full))
		printf("%lu %i is eating\n", get_ms() - philo->data->start_ms,
			philo->id);
	pthread_mutex_unlock(&(philo->data->printf_mutex));
	pthread_mutex_lock(&(philo->data->data_mutex));
	philo->eating_numbers += 1;
	philo->last_eat = get_ms();
	philo->is_eating = 1;
	pthread_mutex_unlock(&(philo->data->data_mutex));
	ft_msleep((philo)->data->tte);
	pthread_mutex_lock(&(philo->data->data_mutex));
	philo->is_eating = 0;
	pthread_mutex_unlock(&(philo->data->data_mutex));
	leave_forks(philo);
}

static void	do_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->printf_mutex));
	if (!(philo->data->is_died || philo->data->is_full))
		printf("%lu %i is sleeping\n", get_ms() - philo->data->start_ms,
			philo->id);
	pthread_mutex_unlock(&(philo->data->printf_mutex));
}

static void	do_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->printf_mutex));
	if (!(philo->data->is_died || philo->data->is_full))
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
	if (philo->id % 2 == 0)
		usleep(50);
	if (philo->data->p_nbr == 1)
	{
		take_fork_left(philo);
		ft_msleep(philo->data->ttd);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (NULL);
	}
	while (!philo->data->is_died && !philo->data->is_full)
	{
		do_eat(philo);
		do_sleep(philo);
		ft_msleep((philo)->data->tts);
		do_think(philo);
		usleep(500);
	}
	return (NULL);
}
