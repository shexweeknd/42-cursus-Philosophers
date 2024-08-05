/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:26:04 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/05 14:16:31 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_lock(&(philo->data->printf_mutex));
	// printf("%lu philo %i has taken a fork number :%i\n", get_ms()
	// 	- philo->data->start_ms, philo->id, philo->left_fork);
	printf("%lu %i has taken a fork\n", get_ms() - philo->data->start_ms,
		philo->id);
	pthread_mutex_unlock(&(philo->data->printf_mutex));
}

static void	take_fork_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_lock(&(philo->data->printf_mutex));
	// printf("%lu philo %i has taken fork number :%i\n", get_ms()
	// 	- philo->data->start_ms, philo->id, philo->right_fork);
	printf("%lu %i has taken a fork\n", get_ms() - philo->data->start_ms,
		philo->id);
	pthread_mutex_unlock(&(philo->data->printf_mutex));
}

static void	leave_fork_left(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

static void	leave_fork_right(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

static void	do_eat(t_philo *philo)
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
	pthread_mutex_lock(&(philo->data->printf_mutex));
	printf("%lu %i is eating\n", get_ms() - philo->data->start_ms, philo->id);
	pthread_mutex_unlock(&(philo->data->printf_mutex));
	pthread_mutex_lock(&(philo->data->data_mutex));
	philo->eating_numbers += 1;
	philo->last_eat = get_ms();
	pthread_mutex_unlock(&(philo->data->data_mutex));
	ft_usleep((philo)->data->time_to_eat);
	if (philo->id % 2 == 0)
	{
		leave_fork_left(philo);
		leave_fork_right(philo);
	}
	else
	{
		leave_fork_right(philo);
		leave_fork_left(philo);
	}
}

static void	do_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->printf_mutex));
	printf("%lu %i is sleeping\n", get_ms() - philo->data->start_ms, philo->id);
	pthread_mutex_unlock(&(philo->data->printf_mutex));
}

static void	do_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->printf_mutex));
	printf("%lu %i is thinking\n", get_ms() - philo->data->start_ms, philo->id);
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
		ft_usleep((philo)->data->time_to_sleep);
		do_think(philo);
	}
	return (NULL);
}
