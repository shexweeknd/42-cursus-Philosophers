/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:01:03 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/09 15:04:54 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	if (!get_die_state(philo->data))
	{
		pthread_mutex_lock(&(philo->data->printf_mutex));
		printf("%lu %i has taken a fork\n", get_ms() - philo->data->start_ms,
			philo->id);
		pthread_mutex_unlock(&(philo->data->printf_mutex));
	}
}

static void	take_fork_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	if (!get_die_state(philo->data))
	{
		pthread_mutex_lock(&(philo->data->printf_mutex));
		printf("%lu %i has taken a fork\n", get_ms() - philo->data->start_ms,
			philo->id);
		pthread_mutex_unlock(&(philo->data->printf_mutex));
	}
}

void	take_forks(t_philo *philo)
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
}

void	leave_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	}
}
