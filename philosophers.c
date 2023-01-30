/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 21:41:46 by rkabzins          #+#    #+#             */
/*   Updated: 2023/01/15 21:41:47 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_global	global;

	if (argc < 5 || argc > 6)
	{
		printf("tt = time to.\nAnything in the \"[]\" braces is optional.\n");
		printf("%sUsage: %s%s num_philo's ", K_GREEN, K_CYAN, argv[0]);
		printf("ttdie tteat ttsleep [num_of_eat]\n");
		return (1);
	}
	init_global(&global, argc, argv);
	gettimeofday(&global.start_time, NULL);
	init_structs(&global);
	while (1)
	{
		if (global.philo_dead)
			close_all(&global);
	}
}

void	init_global(t_global *global, int argc, char **argv)
{
	int	i;

	i = atoi(argv[1]);
	global->num_philosophers = i;
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
			return (errormsg("Error with mutex initiation."));
	}
	global->philosophers = calloc(global->num_philosophers, sizeof(t_philosopher *));
	pthread_create(&global->monitor, NULL, monitor, global);
	i = -1;
	while (++i < global->num_philosophers)
		global->philosophers[i] = init_philo(global, i);
	pthread_join(global->monitor, NULL);
	i = -1;
	while(++i < global->num_philosophers)
		pthread_join(global->philosophers[i]->thread_id, NULL);
	return (0);
}

t_philosopher	*init_philo(t_global *global, int i)
{
	t_philosopher *philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	philosopher->id = i + 1;
	philosopher->state = PHILO_STATE_THINKING;
	philosopher->last_meal_time = 0;
	philosopher->num_meals = 0;
	philosopher->global = global;
	philosopher->left_fork = global->forks[i];
	philosopher->right_fork = global->forks[(i + 1) % global->num_philosophers];
	pthread_create(&philosopher->thread_id, NULL, philosopher_behaviour, philosopher);
	return (philosopher);
}

int	errormsg(char *str)
{
	printf("\x1B[31;1;4m" " Error\v %s\n" "\x1B[0m", str);
	return (1);
}

void	close_all(t_global *global)
{
	int	i;

	global->philo_dead = true;
	i = -1;
	while (++i < global->num_philosophers)
		free(global->philosophers[i]);
	i = -1;
	while (++i < global->num_philosophers)
	{
		pthread_mutex_destroy(global->forks[i]);
		printf("Close Forks %d\n", i + 1);
		free(global->forks[i]);
	}
	free(global->philosophers);
	free(global->forks);
}

void	*philosopher_behaviour(void *philosopher)
{
	t_philosopher	*self;

	self = (t_philosopher *)philosopher;
	self->last_meal_time = get_elapsed_time(self->global);
	if (self->state == PHILO_STATE_THINKING)
	{
		pthread_mutex_lock(self->left_fork);
		pthread_mutex_lock(self->right_fork);

	}
	pthread_mutex_unlock(self->left_fork);
	pthread_mutex_unlock(self->right_fork);
}

void	*monitor(void *args)
{
	t_global		*global;
	int				i;
	t_philosopher	*current_philo;
	long			elapsed_time;

	global = (t_global *)args;
	while (!global->philo_dead)
	{
		i = -1;
		while (++i < global->num_philosophers && !global->philo_dead)
		{
			elapsed_time = get_elapsed_time(global);
			current_philo = global->philosophers[i];
			if (!current_philo)
				continue;
			if ((elapsed_time - current_philo->last_meal_time) >= global->time_to_die)
			{
				global->philo_dead = true;
				printf("[%ld] Philosopher %d has died!\n", elapsed_time, current_philo->id);
			}
		}
	}
}

long	get_elapsed_time(t_global *global)
{
	struct timeval	now;
	long	elapsed_time;

	gettimeofday(&now, NULL);
	elapsed_time = (now.tv_sec - global->start_time.tv_sec) * 1000;
    elapsed_time += (now.tv_usec - global->start_time.tv_usec) / 1000;
	return (elapsed_time);
}
/*
check time-to-die against time-since-last-eaten
attempt to pick up forks
if unable to pick up forks, put forks down, wait 5ms and attempt it again.
eat for time-to-eat
update time-since-last-eaten
put down forks
sleep for time-to-sleep
Main thread checking time-to-die against time-since-last-eaten every ms for all Philosophers.
*/