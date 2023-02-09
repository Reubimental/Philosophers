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

long	get_time(t_global *global)
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

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (n--)
		*ptr++ = 0;
}

void	*_calloc(size_t n, size_t size)
{
	void	*ptr;

	if (!n || !size)
	{
		size = 1;
		n = size;
	}
	ptr = malloc(n * size);
	if (ptr)
		ft_bzero(ptr, n * size);
	return (ptr);
}
