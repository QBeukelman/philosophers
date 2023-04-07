/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_eating.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 11:39:26 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2023/04/07 10:13:23 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_eating(t_philo *self)
{
	ft_start_eating(self);
		
	pthread_mutex_lock(&self->data->mutex[MEALS]);
	self->last_meal = ft_abs_time ();
	self->meal_counter++;
	pthread_mutex_unlock(&self->data->mutex[MEALS]);
	
	ft_msleep(self->data->time_eat);
	ft_finish_eating(self);

	return (SUCCESS);
}

int	ft_start_eating(t_philo *self)
{
	pthread_mutex_lock(&self->fork[ft_min(self->l_fork, self->r_fork)]);
	pthread_mutex_lock(&self->fork[ft_max(self->l_fork, self->r_fork)]);
	ft_print(self, "has taken a fork");
	ft_print(self, "has taken a fork");
	ft_print(self, "is eating");

	return (SUCCESS);
}

int	ft_finish_eating(t_philo *self)
{
	pthread_mutex_unlock(&self->fork[ft_min(self->l_fork, self->r_fork)]);
	pthread_mutex_unlock(&self->fork[ft_max(self->l_fork, self->r_fork)]);
	return (SUCCESS);
}
