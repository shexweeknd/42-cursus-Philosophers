/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:16:43 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/06 11:02:54 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_ms(void)
{
	unsigned long	result;
	t_time			time_val;

	gettimeofday(&time_val, NULL);
	result = (unsigned long)(time_val.tv_sec * 1e3 + (time_val.tv_usec / 1e3));
	return (result);
}

unsigned long	get_us(void)
{
	unsigned long	result;
	t_time			time_val;

	gettimeofday(&time_val, NULL);
	result = (unsigned long)(time_val.tv_sec * 1e6 + time_val.tv_usec);
	return (result);
}
