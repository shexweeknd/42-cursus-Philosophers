/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:26:04 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/03 05:03:50 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork_left(t_philo *philo)
{
	pthread_mutex_lock(&(((philo->data->forks)[(philo->pos + 1)
				% (philo->data->philos_nbr)])));
	printf("[%lu] philo %i has taken a fork number :%i\n", get_ms()
		- philo->data->start_ms, philo->id, (philo->pos + 1)
		% (philo->data->philos_nbr));
}

static void	take_fork_right(t_philo *philo)
{
	pthread_mutex_lock(&((philo->data->forks)[philo->pos]));
	printf("[%lu] philo %i has taken fork number :%i\n", get_ms()
		- philo->data->start_ms, philo->id, philo->pos);
}

static void	leave_fork_left(t_philo *philo)
{
	pthread_mutex_unlock(&((philo->data->forks)[(philo->pos + 1)
			% (philo->data->philos_nbr)]));
}

static void	leave_fork_right(t_philo *philo)
{
	pthread_mutex_unlock(&((philo->data->forks)[philo->pos]));
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
	printf("[%lu] philo %i is eating\n", get_ms() - philo->data->start_ms,
		philo->id);
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
	pthread_mutex_lock(&(philo->data->data_mutex));
	philo->eating_numbers += 1;
	philo->last_eat = get_ms();
	usleep(philo->data->time_to_eat * 1e3);
	pthread_mutex_unlock(&(philo->data->data_mutex));
}

static void	do_sleep(t_philo *philo)
{
	printf("[%lu] philo %i is sleeping\n", get_ms() - philo->data->start_ms,
		philo->id);
	usleep(philo->data->time_to_sleep * 1e3);
}

static void	do_think(t_philo *philo)
{
	printf("[%lu] philo %i is thinking\n", get_ms() - philo->data->start_ms,
		philo->id);
}

void	*simule(void *arg)
{
	t_philo	*philo;
	int		is_died;

	philo = (t_philo *)arg;
	while (get_us() != philo->data->start_us + 500)
		;
	pthread_mutex_lock(&(philo->data->data_mutex));
	is_died = philo->data->is_died;
	pthread_mutex_unlock(&(philo->data->data_mutex));
	while (!is_died)
	{
		do_eat(philo);
		usleep((philo)->data->time_to_eat);
		do_sleep(philo);
		usleep((philo)->data->time_to_sleep);
		do_think(philo);
		pthread_mutex_lock(&(philo->data->data_mutex));
		is_died = philo->data->is_died;
		pthread_mutex_unlock(&(philo->data->data_mutex));
	}
	return (NULL);
}
