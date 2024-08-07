/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:38:15 by hramaros          #+#    #+#             */
/*   Updated: 2024/08/07 10:53:34 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
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
	int					etf;
	int					is_died;
	int					is_full;
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

// functions for the philosophers core program
void					*simule(void *arg);
void					init_starting(t_philo *p_array, long p_nbr);
int						create_threads(t_philo *p_array, char **argv);
void					d_mutex_and_free(t_philo *p_array);

// philo actions utils functions
void					take_forks(t_philo *philo);
void					leave_forks(t_philo *philo);

// utils functions for everybody
long					ft_atol(const char *str);
unsigned long			get_ms(void);
unsigned long			get_us(void);
void					ft_msleep(unsigned long timestamp);

// functions for input checker
int						is_valid_data(t_data *data);
int						is_any_dying(t_philo *p);
int						is_everyone_full(t_philo *p);

// declaration for special case: data->p_nbr == 1
void					take_fork_left(t_philo *philo);

// functions for debugging
void					print_philos(t_philo *philo);

#endif
