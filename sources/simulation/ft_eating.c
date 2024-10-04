/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:39:26 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/10/04 13:49:04 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_eating(t_philo *self)
{
	ft_start_eating(self);
	pthread_mutex_lock(&self->data->mutex[MEALS]);
	self->last_meal = ft_abs_time ();
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
	pthread_mutex_lock(&self->data->mutex[MEALS]);
	self->meal_counter++;
	pthread_mutex_unlock(&self->data->mutex[MEALS]);
	return (SUCCESS);
}
