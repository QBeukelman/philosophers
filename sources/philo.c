/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 10:23:02 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/04/15 21:27:32 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
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
 */

	// ! Add to struct, which philo died.
	// ! Catch the death in the main thread, after a delay
	// ./philo 2 310 200 100
	
	// It is possible that a philo dies when it shouldn't
	// ./philo 4 800 200 200
	// ./philo 4 410 200 200

	// With flags fsanitize=thread, data race
	// ./philo 5 800 100 100 5

	// With flags fsanitize=thread, leak
	// ./philo 2 310 200 100


#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_philo			*philos_array;
	t_data			*data;

	if (ft_check_args(argc, argv) != SUCCESS)
		return (EXIT_FAILURE);

	ft_init(&philos_array, &data, argc, argv);

	ft_simulator (philos_array, data);
	
	return (EXIT_SUCCESS);
}
