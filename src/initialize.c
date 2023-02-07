/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:34:04 by rkabzins          #+#    #+#             */
/*   Updated: 2023/01/30 22:34:05 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_global(t_global *global, int argc, char **argv)
{
	int	i;

	i = atoi(argv[1]);
	global->num_philosophers = i;
	global->meals_finished = i;
	global->time_to_die = atoi(argv[2]);
	global->time_to_eat = atoi(argv[3]);
	global->time_to_sleep = atoi(argv[4]);
	global->num_meals_each = 0;
	global->philo_dead = false;
	if (argc == 6)
		global->num_meals_each = atoi(argv[5]);
}

int	init_structs(t_global *global)
{
	int				i;

	global->forks = (pthread_mutex_t **) malloc(sizeof(pthread_mutex_t *)
			* global->num_philosophers);
	i = -1;
	while (++i < global->num_philosophers)
	{
		global->forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(global->forks[i], NULL))
			return (printf("\x1B[31;1;4m" " Error\v %s\n" "\x1B[0m",
					"Error with mutex initialization."));
	}
	global->philosophers = calloc(global->num_philosophers,
			sizeof(t_philosopher *));
	pthread_create(&global->monitor, NULL, monitor, global);
	i = -1;
	while (++i < global->num_philosophers)
		global->philosophers[i] = init_philo(global, i);
	pthread_join(global->monitor, NULL);
	i = -1;
	while (++i < global->num_philosophers)
	{
		printf("Philo %d joining\n", global->philosophers[i]->id);
		pthread_join(global->philosophers[i]->thread_id, NULL);
		printf("Philo %d joined\n", i + 1);
	}
	printf("Post-Join Philo\n");
	return (0);
}

t_philosopher	*init_philo(t_global *global, int i)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	philosopher->id = i + 1;
	philosopher->state = PHILO_STATE_THINKING;
	philosopher->last_meal_time = 0;
	philosopher->num_meals = 0;
	philosopher->global = global;
	philosopher->left_fork = global->forks[i];
	philosopher->right_fork = global->forks[(i + 1) % global->num_philosophers];
	pthread_create(&philosopher->thread_id, NULL,
		philosopher_behaviour, philosopher);
	return (philosopher);
}
