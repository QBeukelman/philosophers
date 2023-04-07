/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_check_end_conditions.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 11:17:31 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/04/07 10:04:47 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// ===== [ died ] =====
int	ft_set_is_dead(t_philo *p_a, t_data *data, unsigned long l_meal)
{
	if (l_meal && (ft_abs_time() - l_meal) > (unsigned long)data->time_die)
	{
		data->id_died = p_a->id;
		data->time_of_death = ft_rel_time(p_a->data->sim_begin);
		
		ft_died(data);
		return (SUCCESS);
	}
	return (FAILURE);
}

void	ft_died(t_data *data)
{
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
