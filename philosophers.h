/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42adel.org.au>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 21:41:52 by rkabzins          #+#    #+#             */
/*   Updated: 2023/01/15 21:41:54 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>

# define K_NORMAL  "\x1B[0m"
# define K_RED  "\x1B[31m"
# define K_GREEN  "\x1B[32m"
# define K_YELLOW  "\x1B[33m"
# define K_BLUE  "\x1B[34m"
# define K_MAGENTA  "\x1B[35m"
# define K_CYAN  "\x1B[36m"
# define K_WHITE  "\x1B[37m"

# define THINKING 1
# define EATING 2
# define SLEEPING 3

typedef struct s_philosopher
{
	int				id;
	int				state;
	int				num_meals;
	long			last_meal_time;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philosopher;

typedef struct s_global
{
	t_philosopher	**philosopher;
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals_each;
	pthread_mutex_t	**forks;
	struct timeval	start_time;
}	t_global;

void			init_structs(t_global *global);
t_philosopher	*init_philo(t_global *global, t_philosopher *new_philosopher,
					int i);
int				init_mutex(t_global	*global);
int				errormsg(char *str);
void			close_all(t_global *global);

#endif
