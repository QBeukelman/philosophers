/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_simulation_thread.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:27:31 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/23 15:28:03 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void		*ft_simulation_thread(void *arg)
{
	t_philo		*self;

	self = (t_philo *)arg;

	// When a philo treis to pick up fork, 
	// it executes a wait() operation on that semaphore.


	// Every second philo waits to start eating
	if (self->id % 2 == 0)
	{
		ft_print(self, "is thinking");
		ft_msleep(self->data->time_eat);
	}
	

	while (1)
	{
		if (ft_check_die(self) != SUCCESS)
			break ;
		ft_eating(self);
		ft_sleep(self);
		ft_think(self);
	}
	
	return (NULL);
}

int		ft_check_die(t_philo *self)
{
	pthread_mutex_lock(&self->data->mutex[DIED]);
	if (self->data->died == TRUE)
	{
		return (FALSE);
	}
	pthread_mutex_unlock(&self->data->mutex[DIED]);
	return (SUCCESS);
}

// ===== [ observe ] =====
static int		ft_observe_thread(t_philo *self, t_data *data)
{
	int				i;
	unsigned long	l_meal;
	
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mutex[MEALS]);
		l_meal = self[i].last_meal;
		pthread_mutex_unlock(&data->mutex[MEALS]);
		if (ft_set_are_done(self, data, l_meal) != SUCCESS)
			break ;
		// ft_set_is_dead()
	}

	return (SUCCESS);
}

static int	ft_set_are_done(t_philo *self, t_data *data, unsigned long l_meal)
{
	if (l_meal && ft_all_done(self, data))
	{
		ft_done(data);
		return (FAILURE);
	}
	return (SUCCESS);
}

// static int	ft_set_is_dead(t_philo *self, t_data *data)
// static int	ft_all_done(t_philo *self, t_data *data)
// void		ft_done(t_data *data)