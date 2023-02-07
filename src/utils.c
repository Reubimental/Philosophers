/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:34:11 by rkabzins          #+#    #+#             */
/*   Updated: 2023/01/30 22:34:12 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_elapsed_time(t_global *global)
{
	long	elapsed_time;

	gettimeofday(&global->now, NULL);
	elapsed_time = (global->now.tv_sec - global->start_time.tv_sec) * 1000;
	elapsed_time += (global->now.tv_usec - global->start_time.tv_usec) / 1000;
	return (elapsed_time);
}

long long	timestamp(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}

void	*monitor(void *args)
{
	t_global		*global;
	int				i;
	t_philosopher	*current_philo;

	global = (t_global *)args;
	while (!global->philo_dead && global->meals_finished != 0)
	{
		i = -1;
		while (++i < global->num_philosophers && !global->philo_dead)
		{
			current_philo = global->philosophers[i];
			if (!current_philo)
				continue ;
			if ((get_elapsed_time(global) - current_philo->last_meal_time)
				>= global->time_to_die)
			{
				global->philo_dead = current_philo->id;
				printf("---[%ld] Philosopher %d has died!\n",
					get_elapsed_time(global), global->philo_dead);
				break ;
			}
		}
	}
	printf("I GOT HERE\n");
	return (NULL);
}

void	close_all(t_global *global)
{
	int	i;

	printf("Closing\n");
	i = -1;
	if (global->philo_dead)
		printf("[%ld] Philosopher %d has died!\n", get_elapsed_time(global),
			global->philo_dead);
	while (++i < global->num_philosophers)
		free(global->philosophers[i]);
	i = -1;
	while (++i < global->num_philosophers)
	{
		pthread_mutex_destroy(global->forks[i]);
		free(global->forks[i]);
	}
	free(global->philosophers);
	free(global->forks);
}

void	sleep_interruptable(t_global *global, int time_to_activity)
{
	long long	time_stamp;

	time_stamp = timestamp();
	while (!(global->philo_dead))
	{
		if ((timestamp() - time_stamp) >= time_to_activity
			|| global->philo_dead)
			break ;
		usleep(50);
	}
}
