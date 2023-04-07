/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_simulator.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:27:07 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/04/07 13:56:39 by quentinbeuk   ########   odam.nl         */
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
		return (free (th), FAILURE);
	}
	if (ft_create_threads(philos_array, data, th) != SUCCESS)
		return (FAILURE);
		
	ft_iniciate_observe(philos_array, data, th);
	
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join (th[i], NULL))
			return (FAILURE);
		i++;
	}
	ft_exit(philos_array, data, th);
	return (SUCCESS);
}


int	ft_iniciate_observe(t_philo *philos_array, t_data *data, pthread_t *th)
{
	if (ft_observe_thread(philos_array, data) != SUCCESS)
	{	
		if (data->done == TRUE)
			ft_printf_all_done(philos_array);
		if (data->died == TRUE)
			ft_printf_died(data);
		(void)free (th);
		return (FAILURE);
	}
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
			(void)free (th);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
