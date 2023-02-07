/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:33:55 by rkabzins          #+#    #+#             */
/*   Updated: 2023/01/30 22:33:58 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	handle_thinking(t_philosopher *self)
{
	if (self->global->philo_dead)
		return ;
	if (pthread_mutex_lock(self->left_fork) == 0)
	{
		printf("[%ld] Philosopher %d has taken Left Fork.\n",
			get_elapsed_time(self->global), self->id);
		if (self->global->philo_dead)
			return ;
		if (pthread_mutex_lock(self->right_fork) == 0)
		{
			self->last_meal_time = get_elapsed_time(self->global);
			printf("[%ld] Philosopher %d has taken Right Fork.\n",
				get_elapsed_time(self->global), self->id);
			printf("[%ld] Philosopher %d is Eating.\n",
				get_elapsed_time(self->global), self->id);
			self->state = PHILO_STATE_EATING;
			return ;
		}
		else
			handle_no_fork(self);
	}
}

void	handle_eating(t_philosopher *self)
{
	sleep_interruptable(self->global, self->global->time_to_eat);
	if (self->global->philo_dead)
		return ;
	if (!pthread_mutex_unlock(self->left_fork)
		&& !pthread_mutex_unlock(self->right_fork))
	{
		printf("[%ld] Philosopher %d has put down both forks.\n",
			get_elapsed_time(self->global), self->id);
	}
	self->num_meals++;
	if (self->num_meals == self->global->num_meals_each)
		self->global->meals_finished--;
	self->state = PHILO_STATE_SLEEPING;
	self->time_sleep_start = get_elapsed_time(self->global);
	printf("[%ld] Philosopher %d is Sleeping.\n",
		get_elapsed_time(self->global), self->id);
}

void	handle_sleeping(t_philosopher *self)
{
	sleep_interruptable(self->global, self->global->time_to_sleep);
	if (self->global->philo_dead)
		return ;
	self->state = PHILO_STATE_THINKING;
	printf("[%ld] Philosopher %d is Thinking.\n",
		get_elapsed_time(self->global), self->id);
}

void	handle_no_fork(t_philosopher *self)
{
	if (self->global->philo_dead)
		return ;
	printf("[%ld] Philosopher %d has no Right Fork available.\n",
		get_elapsed_time(self->global), self->id);
	if (!pthread_mutex_unlock(self->left_fork))
	{
		printf("[%ld] Philosopher %d has put down Left Fork.\n",
			get_elapsed_time(self->global), self->id);
	}
}

void	*philosopher_behaviour(void *philosopher)
{
	t_philosopher	*self;

	self = (t_philosopher *)philosopher;
	printf("[%ld] Philosopher %d is Thinking.\n",
		get_elapsed_time(self->global), self->id);
	while (!self->global->philo_dead && self->global->meals_finished != 0)
	{
		if (self->state == PHILO_STATE_THINKING && !self->global->philo_dead)
			handle_thinking(self);
		if (self->state == PHILO_STATE_EATING && !self->global->philo_dead)
			handle_eating(self);
		if (self->state == PHILO_STATE_SLEEPING && !self->global->philo_dead)
			handle_sleeping(self);
		if (self->global->philo_dead)
			break ;
	}
	return (NULL);
}
