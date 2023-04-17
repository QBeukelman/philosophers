/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_simulator.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:27:07 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/04/17 08:58:24 by qbeukelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_simulator(t_philo *philos_array, t_data *data)
{
	int			i;
	pthread_t	*th;

	th = malloc (sizeof (pthread_t) * (size_t)data->philo_nb);
	if (th == NULL)
	{
		ft_print_error("ERROR: Not enough memory to perform malloc().");
		return (ft_exit(philos_array, data, th), FAILURE);
	}
	if (ft_create_threads(philos_array, data, th) != SUCCESS)
		return (ft_exit(philos_array, data, th), FAILURE);
	if (ft_observe_thread(philos_array, data) != SUCCESS)
	{
		i = 0;
		while (i < data->philo_nb)
		{
			if (pthread_detach(th[i]))
				return (ft_exit(philos_array, data, th), FAILURE);
			i++;
		}
	}
	ft_end_conditions(philos_array, data);
	ft_exit(philos_array, data, th);
	return (SUCCESS);
}

int	ft_create_threads(t_philo *philos_array, t_data *data, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create (&th[i], 0, ft_sim_thread, (void *)&philos_array[i]))
		{
			while (i >= 0)
			{
				pthread_join (th[i], NULL);
				i--;
			}
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

void	ft_end_conditions(t_philo *philos_array, t_data *data)
{
	if (data->done == TRUE)
		ft_printf_all_done(philos_array);
	if (data->died == TRUE)
		ft_printf_died(data);
}
