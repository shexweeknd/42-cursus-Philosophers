/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:38:15 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/03 05:05:29 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct timeval	t_time;

typedef struct s_data
{
	int					philos_nbr;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_die;
	int					eat_to_full;
	int					is_died;
	unsigned long		start_ms;
	unsigned long		start_us;
	pthread_mutex_t		data_mutex;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					pos;
	int					eating_numbers;
	unsigned long		last_eat;
	pthread_mutex_t		philo_mutex;
	pthread_t			thread;
	t_data				*data;
}						t_philo;

// fonction pour les philos
void					*simule(void *arg);
unsigned long			get_ms(void);
unsigned long			get_us(void);

// fonctions utils pour le parse des args
long					ft_atol(const char *str);

// fonctions pour le debug
void					print_philos(t_philo *philo);

#endif
