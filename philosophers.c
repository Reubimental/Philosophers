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
	t_global		global;
	int				i;

	if (argc < 5 || argc > 6)
	{
		printf("tt = time to.\nAnything in the \"[]\" braces is optional.\n");
		printf("%sUsage: %s%s num_philo's ", K_GREEN, K_CYAN, argv[0]);
		printf("ttdie tteat ttsleep [num_of_eat]\n");
		return (1);
	}
	i = atoi(argv[1]);
	global.num_philosophers = i;
	global.time_to_die = atoi(argv[2]);
	global.time_to_eat = atoi(argv[3]);
	global.time_to_sleep = atoi(argv[4]);
	global.num_meals_each = 0;
	if (argc == 6)
		global.num_meals_each = atoi(argv[5]);
	gettimeofday(&global.start_time, NULL);
	init_structs(&global);
	if (init_mutex(&global))
		return (errormsg("Error with mutex initiation."));
	close_all(&global);
}

void	init_structs(t_global *global)
{
	int				i;

	global->forks = (pthread_mutex_t **) malloc(sizeof(pthread_mutex_t *)
			* global->num_philosophers);
	i = -1;
	printf("%ld\n", sizeof(pthread_mutex_t));
	while (++i < global->num_philosophers)
		global->forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	global->philosophers = malloc(sizeof(t_philosopher *) * global->num_philosophers);
	i = -1;
	while (++i < global->num_philosophers)
		global->philosophers[i] = init_philo(global, i);
	i = -1;
	while(++i < global->num_philosophers)
		pthread_join(global->philosopher[i]->thread_id, NULL);
}

t_philosopher	*init_philo(t_global *global, int i)
{
	t_philosopher *philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	philosopher->id = i + 1;
	philosopher->state = THINKING;
	philosopher->last_meal_time = 0;
	philosopher->num_meals = 0;
	philosopher->left_fork = global->forks[i];
	if ((i + 1) == global->num_philosophers)
		philosopher->right_fork = global->forks[0];
	else
		philosopher->right_fork = global->forks[i + 1];
	pthread_create(&philosopher->thread_id, NULL, philosopher_behaviour, &global);
	return (philosopher);
}

int	init_mutex(t_global	*global)
{
	int				i;
	pthread_mutex_t	*mutex;

	i = -1;
	while (++i < global->num_philosophers)
	{
		mutex = global->forks[i];
		if (pthread_mutex_init(mutex, NULL))
			return (1);
	}
	return (0);
}

int	errormsg(char *str)
{
	printf("\x1B[31;1;4m" " Error\n    %s\n" "\x1B[0m", str);
	return (1);
}

void	close_all(t_global *global)
{
	int	i;

	i = -1;
	while (++i < global->num_philosophers)
	{
		pthread_join(global->philosophers[i]->thread_id, NULL);
		free(global->philosophers[i]);
	}
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

void	*philosopher_behaviour(void *global)
{

}