/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_eating_operations.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 11:15:14 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/04/03 11:15:55 by qbeukelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// ===== [ sleep ] =====
int	ft_sleep(t_philo *self)
{
	ft_print(self, "is sleeping");
	ft_msleep(self->data->time_sleep);
	return (SUCCESS);
}

// ===== [ think ] =====
int	ft_think(t_philo *self)
{
	ft_print(self, "is thinking");
	ft_msleep(self->data->time_think);
	return (SUCCESS);
}

// ===== [ done ] =====
int	ft_is_done(t_philo *self)
{
	pthread_mutex_lock(&self->data->mutex[DONE]);
	if (self->data->done)
	{
		pthread_mutex_unlock(&self->data->mutex[DONE]);
		return (TRUE);
	}
	pthread_mutex_unlock(&self->data->mutex[DONE]);
	return (FALSE);
}

int	ft_max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
