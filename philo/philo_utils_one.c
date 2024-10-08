/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:21:02 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/07 10:53:18 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	ret;

	if (!str)
		return (INT_MIN);
	i = 0;
	while (is_space(str[i]))
		i++;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	ret = 0;
	while (is_number(str[i]))
	{
		ret = ret * 10 + (str[i] - 48);
		i++;
	}
	ret *= sign;
	return (ret);
}

void	ft_msleep(unsigned long timestamp)
{
	unsigned long	curr_ms;

	curr_ms = get_ms();
	while (get_ms() - curr_ms < timestamp)
		usleep(1);
}

void	d_mutex_and_free(t_philo *p_array)
{
	int	index;

	index = 0;
	while (index < p_array->data->p_nbr)
	{
		pthread_mutex_destroy(&p_array->data->forks[index]);
		index++;
	}
	pthread_mutex_destroy(&p_array->data->data_mutex);
	pthread_mutex_destroy(&p_array->data->printf_mutex);
	free(p_array->data->forks);
	free(p_array->data);
	free(p_array);
}
