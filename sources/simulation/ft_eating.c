/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_eating.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 11:39:26 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2023/03/23 12:58:08 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_eating(t_philo *self)
{
	// start eating
	if (ft_start_eating(self) != SUCCESS)
		return (FAILURE);

	pthread_mutex_lock(&self->data->mutex[MEALS]);
	// lock meals
	self->last_meal = ft_abs_time ();
	self->meal_counter++;
	// unlock meals
	pthread_mutex_lock(&self->data->mutex[MEALS]);

	// finish eating
	ft_sleep(self);
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
	ft_msleep(self->data->time_eat);

	ft_finish_eating(self);
	return (SUCCESS);
}

void	ft_finish_eating(t_philo *self)
{
	pthread_mutex_unlock(&self->fork[self->l_fork]);
	pthread_mutex_unlock(&self->fork[self->r_fork]);
}

void	ft_sleep(t_philo *self)
{
	ft_print(self, "is sleeping");
	ft_msleep(self->data->time_sleep);
}

void	ft_think(t_philo *self)
{
	ft_print(self, "is thinking");
	ft_msleep(self->data->time_think);
}



// ===== [ done ] =====