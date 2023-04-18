/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 10:23:02 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/04/17 23:09:54 by quentinbeuk   ########   odam.nl         */
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

#include "../includes/philo.h"

void	ft_show_leaks(void)
{
	system("leaks philo");
}

int	main(int argc, char *argv[])
{
	t_philo			*philos_array;
	t_data			*data;

	// atexit(ft_show_leaks);
	if (ft_check_args(argc, argv) != SUCCESS)
		return (EXIT_FAILURE);
	if (ft_init(&philos_array, &data, argc, argv) != SUCCESS)
		return (EXIT_FAILURE);
	ft_simulator (philos_array, data);
	return (EXIT_SUCCESS);
}
