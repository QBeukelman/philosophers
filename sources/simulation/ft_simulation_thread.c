/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation_thread.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:27:31 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/10/04 14:15:06 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static bool	is_done_eating(t_philo *self)
{
	bool	is_done;

	is_done = false;
	pthread_mutex_lock(&self->data->mutex[MEALS]);
	is_done = self->meal_counter == self->data->must_eat;
	pthread_mutex_unlock(&self->data->mutex[MEALS]);
	return (is_done);
}

// ===== [ thread ] =====
void	*ft_sim_thread(void *arg)
{
	t_philo		*self;

	self = (t_philo *)arg;
	if (self->id % 2 == 0)
	{
		ft_msleep(self->data->time_eat);
	}
	while (1)
	{
		if (ft_check_die(self) == TRUE)
			break ;
		if (ft_is_done(self) == TRUE)
			break ;
		if (ft_eating(self) != SUCCESS)
			break ;
		if (is_done_eating(self))
		{
			ft_think(self);
			break ;
		}
		if (ft_sleep(self) == SUCCESS)
			ft_think(self);
	}
	return (NULL);
}

// ===== [ observe ] =====
int	ft_observe_thread(t_philo *philos_array, t_data *data)
{
	int				i;
	unsigned long	l_meal;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philos_array[i].data->mutex[MEALS]);
		l_meal = philos_array[i].last_meal;
		pthread_mutex_unlock(&philos_array[i].data->mutex[MEALS]);
		if (l_meal && (ft_abs_time() - l_meal) > (unsigned long)data->time_die)
		{
			ft_died(philos_array, data);
			return (FAILURE);
		}
		if (l_meal && ft_all_done(philos_array, data) == TRUE)
		{
			ft_done(data);
			return (FAILURE);
		}
		i = (i + 1) % data->philo_nb;
	}
	return (SUCCESS);
}

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
