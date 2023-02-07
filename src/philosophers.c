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

#include "../include/philosophers.h"

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
	close_all(&global);
	if (global.philo_dead)
		printf("%s%sSimulation Ended because Philosopher Died.%s\n",
			K_RED, K_BOLD, K_NORMAL);
	else if (global.meals_finished == 0)
		printf("%s%sSimulation Ended because all meals have been eaten.%s\n",
			K_RED, K_BOLD, K_NORMAL);
}
