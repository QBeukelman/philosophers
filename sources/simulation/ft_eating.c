/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_eating.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 11:39:26 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2023/03/23 13:52:39 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_eating(t_philo *self)
{
	// Start
	if (ft_start_eating(self) != SUCCESS)
		return (FAILURE);

	pthread_mutex_lock(&self->data->mutex[MEALS]);
	self->last_meal = ft_abs_time ();
	self->meal_counter++;
	pthread_mutex_unlock(&self->data->mutex[MEALS]);

	return (SUCCESS);
}

int	ft_start_eating(t_philo *self)
{
	pthread_mutex_lock(&self->fork[self->l_fork]);
	pthread_mutex_lock(&self->fork[self->r_fork]);

	// If L == R (Fail)
	ft_print(self, "has taken a fork");
	ft_print(self, "has taken a fork");
	ft_print(self, "is eating");

		// Wait
	ft_msleep(self->data->time_eat);

	// finish eating
	ft_finish_eating(self);
	return (SUCCESS);
}

int		ft_finish_eating(t_philo *self)
{
	pthread_mutex_unlock(&self->fork[self->l_fork]);
	pthread_mutex_unlock(&self->fork[self->r_fork]);
	return (SUCCESS);
}


// ===== [ sleep ] =====
int		ft_sleep(t_philo *self)
{
	ft_print(self, "is sleeping");
	ft_msleep(self->data->time_sleep);
	return (SUCCESS);
}

// ===== [ think ] =====
int		ft_think(t_philo *self)
{
	ft_print(self, "is thinking");
	ft_msleep(self->data->time_think);
	return (SUCCESS);
}

// ===== [ done ] =====
int		ft_is_done(t_philo *self)
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
