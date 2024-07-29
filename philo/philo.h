/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:38:15 by hramaros          #+#    #+#             */
/*   Updated: 2024/07/29 09:48:16 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

typedef struct s_philosopher
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
}					t_philosopher;

pthread_mutex_t		forks[NUM_PHILOSOPHERS];
t_philosopher		philosophers[NUM_PHILOSOPHERS];

#endif
