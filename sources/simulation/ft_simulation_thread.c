/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_simulation_thread.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:27:31 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/24 10:38:48 by quentinbeuk   ########   odam.nl         */
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
int			ft_observe_thread(t_philo *philos_array, t_data *data)
{
	int				i;
	unsigned long	l_meal;
	
	
	while (1)
	{
		i = 0;
		while (i < data->philo_nb)
		{
			printf("%p", &philos_array[i]);
			pthread_mutex_lock(&data->mutex[MEALS]);
			l_meal = philos_array[i].last_meal;
			pthread_mutex_unlock(&data->mutex[MEALS]);
			ft_set_are_done(&philos_array[i], data, l_meal);
			// ft_set_is_dead()
			usleep (50);
			i++;
		}
		usleep (50);
	}

	return (SUCCESS);
}

static int	ft_set_are_done(t_philo *self, t_data *data, unsigned long l_meal)
{
	if (l_meal && ft_all_done(self, data))
	{
		// ft_done(data);
		return (SUCCESS); // ! Should fail
	}
	return (SUCCESS);
}

// static int	ft_set_is_dead(t_philo *self, t_data *data)


static int	ft_all_done(t_philo *self, t_data *data)
{
	// meal_counter == must_eat;

	pthread_mutex_lock(&self->data->mutex[MEALS]);
	printf("Meal counter: %d, %d, %p\n", self->meal_counter, self->id, data);
	pthread_mutex_unlock(&self->data->mutex[MEALS]);
	usleep (50);
	return (SUCCESS);
}

// void		ft_done(t_data *data)