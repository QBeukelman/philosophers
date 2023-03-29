/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 10:23:02 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/29 10:01:23 by qbeukelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
Viz - https://github.com/nafuka11/philosophers-visualizer
Eg - https://github.com/clemedon/philosophers
Diagrams - https://www.youtube.com/watch?v=V73F3kDSkgs
Article - https://begriffs.com/posts/2020-03-23-concurrent-programming.html
Article - https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/


memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock


 *     i-1   i      i
 *     RFork Philos LFork
 *     ------------------
 *       F2  ← P0 →  F0
 *       F0  ← P1 →  F1
 *       F1  ← P2 →  F2
 * 
 * 
 * 	./philo 4 410 200 200  5
 *  	    +--|---|---|---|-- philo_nb
 *      	   +---|---|---|-- time_die
 *          	   +---|---|-- time_eat
 *              	   +---|-- time_sleep
 * 						   +-- must_eat (optional)

 *     Where F0 belongs to philo P3.

 */

#include "../includes/philo.h"

int		main(int argc, char *argv[])
{
	t_philo			*philos_array;
	t_data			*data;
	
	
	if (ft_check_args(argc, argv) == SUCCESS) // must_eat = 0; philo count = 1;
		printf("Check args: SUCCESS\n");
	else
		printf("Check args: FAILURE\n");


	// Init
	data = malloc(sizeof(t_philo));
	data = ft_init_data(data, argc, argv);

	philos_array = malloc(sizeof(t_philo) * data->philo_nb);
	philos_array = ft_init_philo(philos_array, data);

	printf("Philo[0]->data->nbr: %d\n", philos_array[0].data->philo_nb);
	ft_simulator (philos_array, data);

	free (data);
	free (philos_array);
	return (EXIT_SUCCESS);
}

