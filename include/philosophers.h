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
# include <stdbool.h>

# define K_NORMAL  "\x1B[0m"
# define K_BOLD	"\x1B[1m"
# define K_RED  "\x1B[31m"
# define K_GREEN  "\x1B[32m"
# define K_YELLOW  "\x1B[33m"
# define K_BLUE  "\x1B[34m"
# define K_MAGENTA  "\x1B[35m"
# define K_CYAN  "\x1B[36m"
# define K_WHITE  "\x1B[37m"
# define DEAD	0
# define EATING	1
# define SLEEPING	2
# define THINKING	3
# define LEFT_FORK	4
# define RIGHT_FORK	5
# define PICKUP	6
# define PUTDOWN	7

typedef struct s_global	t_global;

enum	e_PHILO_STATE
{
	PHILO_STATE_THINKING,
	PHILO_STATE_EATING,
	PHILO_STATE_SLEEPING,
	PHILO_STATE_DEAD
};

typedef struct s_philosopher
{
	int					id;
	int					num_meals;
	long				last_meal_time;
	long				time_sleep_start;
	enum e_PHILO_STATE	state;
	pthread_t			thread_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_global			*global;
}	t_philosopher;

typedef struct s_global
{
	t_philosopher	**philosophers;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals_each;
	int				meals_finished;
	int				philo_dead;
	pthread_t		monitor;
	pthread_mutex_t	**forks;
	int				start;
	struct timeval	now;
	struct timeval	start_time;
}	t_global;

t_philosopher	*init_philo(t_global *global, int i);
int				init_structs(t_global *global);
void			close_all(t_global *global);
void			*philosopher_behaviour(void *philosopher);
void			*monitor(void *args);
long			get_time(t_global *global);
void			init_global(t_global *global, int argc, char **argv);
void			handle_left_thinking(t_philosopher *self);
void			handle_right_thinking(t_philosopher *self);
void			handle_eating(t_philosopher *self);
void			handle_sleeping(t_philosopher *self);
void			sleep_interruptable(t_global *global, int time_to_activity);
long long		timestamp(void);
void			ft_bzero(void *str, size_t n);
void			*_calloc(size_t n, size_t size);
void			print_behaviour(long long time, int philo, int state,
					int action);

#endif
