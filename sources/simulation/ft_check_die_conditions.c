/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_check_die_conditions.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 11:17:31 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/04/17 08:59:17 by qbeukelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_died(t_philo *philos_array, t_data *data)
{
	data->id_died = philos_array->id;
	data->time_of_death = ft_rel_time(philos_array->data->sim_begin);
	pthread_mutex_lock (&data->mutex[DIED]);
	data->died = TRUE;
	pthread_mutex_unlock (&data->mutex[DIED]);
}

int	ft_check_die(t_philo *self)
{
	pthread_mutex_lock(&self->data->mutex[DIED]);
	if (self->data->died == TRUE)
	{
		pthread_mutex_unlock(&self->data->mutex[DIED]);
		return (TRUE);
	}
	pthread_mutex_unlock(&self->data->mutex[DIED]);
	return (FALSE);
}
