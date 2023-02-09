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

void	handle_left_thinking(t_philosopher *self)
{
	if (!pthread_mutex_lock(self->left_fork))
		print_behaviour(get_time(self->global), self->id, LEFT_FORK, PICKUP);
	if (!pthread_mutex_lock(self->right_fork))
	{
		if (self->global->philo_dead)
			return ;
		self->last_meal_time = get_time(self->global);
		print_behaviour(get_time(self->global), self->id, RIGHT_FORK, PICKUP);
		print_behaviour(get_time(self->global), self->id, EATING, PICKUP);
		self->state = PHILO_STATE_EATING;
	}
}

void	handle_right_thinking(t_philosopher *self)
{
	if (!pthread_mutex_lock(self->right_fork))
		print_behaviour(get_time(self->global), self->id, RIGHT_FORK, PICKUP);
	if (self->global->philo_dead)
		return ;
	if (!pthread_mutex_lock(self->left_fork))
	{
		if (self->global->philo_dead)
			return ;
		self->last_meal_time = get_time(self->global);
		self->state = PHILO_STATE_EATING;
		print_behaviour(get_time(self->global), self->id, LEFT_FORK, PICKUP);
		print_behaviour(get_time(self->global), self->id, EATING, PICKUP);
	}
}

void	handle_eating(t_philosopher *self)
{
	sleep_interruptable(self->global, self->global->time_to_eat);
	if (self->global->philo_dead)
		return ;
	if (!pthread_mutex_unlock(self->left_fork)
		&& !pthread_mutex_unlock(self->right_fork))
		print_behaviour(get_time(self->global), self->id, LEFT_FORK, PUTDOWN);
	self->num_meals++;
	if (self->num_meals == self->global->num_meals_each)
		self->global->meals_finished--;
	self->state = PHILO_STATE_SLEEPING;
	self->time_sleep_start = get_time(self->global);
	print_behaviour(get_time(self->global), self->id, SLEEPING, PICKUP);
}

void	handle_sleeping(t_philosopher *self)
{
	sleep_interruptable(self->global, self->global->time_to_sleep);
	if (self->global->philo_dead)
		return ;
	self->state = PHILO_STATE_THINKING;
	print_behaviour(get_time(self->global), self->id, THINKING, PICKUP);
}

void	*philosopher_behaviour(void *philosopher)
{
	t_philosopher	*self;

	self = (t_philosopher *)philosopher;
	while (!self->global->start)
		;
	print_behaviour(get_time(self->global), self->id, THINKING, PICKUP);
	while (!self->global->philo_dead && self->global->meals_finished != 0)
	{
		if (self->state == PHILO_STATE_THINKING && self->id % 2 == 0)
			handle_left_thinking(self);
		else if (self->state == PHILO_STATE_THINKING && self->id % 2 != 0)
			handle_right_thinking(self);
		else if (self->state == PHILO_STATE_EATING)
			handle_eating(self);
		else if (self->state == PHILO_STATE_SLEEPING)
			handle_sleeping(self);
	}
	return (NULL);
}
