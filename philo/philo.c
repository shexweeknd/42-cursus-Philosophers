/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:38:06 by hramaros          #+#    #+#             */
/*   Updated: 2024/07/29 09:47:20 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(int id)
{
	printf("Philosopher %d is thinking\n", id);
	usleep(rand() % 1000);
}

void	eat(int id)
{
	printf("Philosopher %d is eating\n", id);
	usleep(rand() % 1000);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	while (1)
	{
		think(philosopher->id);
		pthread_mutex_lock(philosopher->left_fork);
		pthread_mutex_lock(philosopher->right_fork);
		eat(philosopher->id);
		pthread_mutex_unlock(philosopher->right_fork);
		pthread_mutex_unlock(philosopher->left_fork);
	}
	return (NULL);
}

int	main(void)
{
	srand(time(NULL));
	// Initialize forks
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		pthread_mutex_init(&forks[i], NULL);
	}
	// Initialize philosophers
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		philosophers[i].id = i;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % NUM_PHILOSOPHERS];
	}
	// Create philosopher threads
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		pthread_create(&philosophers[i].thread, NULL, philosopher_routine,
			&philosophers[i]);
	}
	// Join philosopher threads
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		pthread_join(philosophers[i].thread, NULL);
	}
	// Destroy mutexes
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		pthread_mutex_destroy(&forks[i]);
	}
	return (0);
}
