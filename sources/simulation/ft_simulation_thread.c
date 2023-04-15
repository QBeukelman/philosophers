/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_simulation_thread.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:27:31 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/04/15 15:22:22 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// ===== [ thread ] =====
void	*ft_sim_thread(void *arg)
{
	t_philo		*self;

	self = (t_philo *)arg;
	if (self->id % 2 == 0)
	{
		usleep(200);
		// ft_print(self, "is thinking");
		// ft_msleep(self->data->time_eat);
	}
	while (1)
	{
		if (ft_check_die(self) == TRUE)
			break ;
		if (ft_is_done(self) == TRUE)
			break ;
		if (ft_eating(self) != SUCCESS)
			break ;
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
		pthread_mutex_lock(&data->mutex[MEALS]);
		l_meal = philos_array[i].last_meal;
		pthread_mutex_unlock(&data->mutex[MEALS]);
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
		usleep(50);
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
