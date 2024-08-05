/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:38:15 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/05 17:02:23 by hramaros         ###   ########.fr       */
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
	int					p_nbr;
	int					tte;
	int					tts;
	int					ttd;
	int					eat_to_full;
	int					is_died;
	unsigned long		start_ms;
	unsigned long		start_us;
	pthread_mutex_t		data_mutex;
	pthread_mutex_t		printf_mutex;
	pthread_mutex_t		*forks;
	t_philo				*p;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					pos;
	int					left_fork;
	int					right_fork;
	int					eating_numbers;
	unsigned long		last_eat;
	pthread_t			thread;
	t_data				*data;
}						t_philo;

// TODO the coms are in english, traduct all coms in english

// fonction pour les p
void					*simule(void *arg);
unsigned long			get_ms(void);
unsigned long			get_us(void);
void					ft_usleep(unsigned long timestamp);
void					d_mutex_and_free(t_philo *p_array);

// fonctions pour les actions utils
void					take_forks(t_philo *philo);
void					leave_forks(t_philo *philo);

// fonctions utils
long					ft_atol(const char *str);
void					init_starting(t_philo *p_array, long p_nbr);
int						create_threads(t_philo *p_array, char **argv);

// fonctions pour le debug
void					print_philos(t_philo *philo);

// fonctions pour le checker
int						is_valid_data(t_data *data);
int						is_any_dying(t_philo *p);

#endif
