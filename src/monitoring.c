/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:16:04 by rkabzins          #+#    #+#             */
/*   Updated: 2023/02/08 15:16:06 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*monitor(void *args)
{
	t_global		*global;
	int				i;
	t_philosopher	*current_philo;

	global = (t_global *)args;
	while (!global->philo_dead && global->meals_finished != 0)
	{
		i = -1;
		while (++i < global->num_philo && !global->philo_dead)
		{
			current_philo = global->philosophers[i];
			if (!current_philo)
				continue ;
			if ((get_time(global) - current_philo->last_meal_time)
				>= global->time_to_die)
			{
				global->philo_dead = current_philo->id;
				break ;
			}
		}
	}
	return (NULL);
}

void	close_all(t_global *global)
{
	int	i;

	i = -1;
	if (global->philo_dead)
		print_behaviour(get_time(global), global->philo_dead, DEAD, DEAD);
	while (++i < global->num_philo)
		free(global->philosophers[i]);
	i = -1;
	while (++i < global->num_philo)
	{
		pthread_mutex_destroy(global->forks[i]);
		free(global->forks[i]);
	}
	free(global->philosophers);
	free(global->forks);
}
