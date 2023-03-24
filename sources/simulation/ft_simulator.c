/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_simulator.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:27:07 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/24 12:56:12 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int		ft_simulator(t_philo *philos_array, t_data *data)
{
	int			i;
	pthread_t	*th;

	th = malloc (sizeof (pthread_t) * (size_t)data->philo_nb);
	if (th == NULL)
		return (FAILURE);


	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create (&th[i], 0, ft_simulation_thread, (void *)&philos_array[i]))
		{
			while (i >= 0)
			{
				pthread_join (th[i], NULL);
				i--;
			}
			(void)free (th);
			return (FAILURE);
		}
		i++;
	}

	// ! Monitoring
	if (ft_observe_thread(philos_array, data) != SUCCESS)
		return (FAILURE); // Destroy mutex

	// ! Join threads
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join (th[i], NULL))
			return (FAILURE);
		i++;
	}

	// ! Destroy mutex

	return (SUCCESS);
}

// Continously check simulations termination conditions
// static int	ft_monitor(t_philo *philo, t_data *data)
// {

// 	return (SUCCESS);
// }

