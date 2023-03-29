/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_simulator.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:27:07 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/29 10:28:50 by qbeukelm      ########   odam.nl         */
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
	{
		ft_destroy_mutexes(philos_array, data);
		(void)free (th);
		return (FAILURE); // Destroy mutex
	}

	// ! Join threads
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join (th[i], NULL))
			return (FAILURE);
		i++;
	}

	pthread_detach (th[i]);

	// ! Destroy mutex
	ft_destroy_mutexes(philos_array, data);
	(void)free (th);

	return (SUCCESS);
}

static void	ft_destroy_mutexes(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_nb)
		pthread_mutex_destroy (&philo->fork[i++]);
	i = 0;
	while (i < M_NUM)
		pthread_mutex_destroy (&data->mutex[i++]);
}
