/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:10:53 by rkabzins          #+#    #+#             */
/*   Updated: 2023/02/08 15:10:55 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_behaviour(long long time, int philo, int state, int action)
{
	if (state == LEFT_FORK)
	{
		if (action == PICKUP)
			printf("[%lld] Philosopher %d picked up Left Fork.\n", time, philo);
		else if (action == PUTDOWN)
			printf("[%lld] Philosopher %d put down both forks.\n", time, philo);
	}
	else if (state == RIGHT_FORK)
	{
		if (action == PICKUP)
			printf("[%lld] Philosopher %d picked up Right Fork.\n", time, philo);
		else if (action == PUTDOWN)
			printf("[%lld] Philosopher %d put down both forks.\n", time, philo);
	}
	else if (state == EATING)
		printf("[%lld] Philosopher %d is Eating.\n", time, philo);
	else if (state == SLEEPING)
		printf("[%lld] Philosopher %d is Sleeping.\n", time, philo);
	else if (state == THINKING)
		printf("[%lld] Philosopher %d is Thinking.\n", time, philo);
	else if (action == DEAD)
		printf("[%lld] Philosopher %d has died!\n", time, philo);
}
