/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sim_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:59:49 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/22 12:07:50 by qbeukelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_print(t_philo *philos_array, char *str)
{
	pthread_mutex_lock (&philos_array->data->mutex[PRINT]);
	if (!ft_check_died (philos_array))
		printf("%lu %d %s\n", ft_rel_time(philos_array->data->sim_begin), philos_array->id, str);
	pthread_mutex_unlock(&philos_array->data->mutex[PRINT]);
}

int		ft_check_died(t_philo *philos_array)
{
	pthread_mutex_lock(&philos_array->data->mutex[DIED]);
	if (philos_array->data->died)
	{
		pthread_mutex_unlock(&philos_array->data->mutex[DIED]);
		return (TRUE);
	}
	pthread_mutex_unlock(&philos_array->data->mutex[DIED]);
	return (FALSE);
}

void	ft_died(t_data *data)
{
	pthread_mutex_lock(&data->mutex[DIED]);
	data->died = TRUE;
	pthread_mutex_unlock(&data->mutex[DIED]);
}

int		ft_check_done(t_philo *philos_array)
{
	pthread_mutex_lock(&philos_array->data->mutex[DONE]);
	if (philos_array->data->done)
	{
		pthread_mutex_unlock(&philos_array->data->mutex[DONE]);
		return (TRUE);
	}
	pthread_mutex_unlock(&philos_array->data->mutex[DONE]);
	return (FALSE);
}

void	ft_done(t_data *data)
{
	pthread_mutex_lock(&data->mutex[DONE]);
	data->done = TRUE;
	pthread_mutex_unlock(&data->mutex[DONE]);
}
