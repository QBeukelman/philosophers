/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_simulation.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:27:31 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/22 13:25:28 by qbeukelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void		*ft_simulation(void *arg)
{
	t_philo		*self;

	self = (t_philo *)arg;


	printf("Thread created with id: %d\n", self->id);
	
	// All even philos wait
	if (self->id % 2 == 0)
	{
		ft_print(self, "is thinking");
		ft_msleep(self->data->time_eat);
	}
	
	// while (1)
	// {
	// 	if (ft_check_died(self))
	// 		break ;
		
	// 	if (ft_eating (self) != SUCCESS)
	// 		break ;
		
	// 	ft_print(self, "is thinking");
	// 	ft_msleep(self->data->time_think);
	// }
	
	return (NULL);
}

static int		ft_eating(t_philo *self)
{
	if (ft_start_eating(self) != SUCCESS)
		return (FAILURE);

	pthread_mutex_lock (&self->data->mutex[MEALS]);
	self->last_meal = ft_abs_time();
	self->meal_counter++;
	pthread_mutex_unlock(&self->data->mutex[MEALS]);
	
	if (ft_check_done(self))
	{
		ft_finish_eating(self);
		return (FAILURE);
	}

	ft_msleep(self->data->time_eat);
	ft_finish_eating (self);
	return (SUCCESS);
}


// start & finish eating
static int		ft_start_eating(t_philo *self)
{
	pthread_mutex_lock(&self->fork[ft_min(self->l_fork, self->r_fork)]);
	ft_print(self, "has taken a fork");
	if (self->l_fork == self->r_fork)
	{
		pthread_mutex_unlock(&self->fork[ft_min(self->l_fork, self->r_fork)]);
		return (FAILURE);	
	}
	pthread_mutex_lock(&self->fork[ft_max(self->l_fork, self->r_fork)]);
	ft_print(self, "has taken a fork");
	ft_print(self, "is eating");

	return (SUCCESS);
}

static int		ft_finish_eating(t_philo *self)
{
	ft_print(self, "is sleeping");
	pthread_mutex_lock(&self->fork[ft_max(self->l_fork, self->r_fork)]);
	pthread_mutex_lock(&self->fork[ft_min(self->l_fork, self->r_fork)]);
	ft_msleep(self->data->time_sleep);
	return (SUCCESS);
}


int		ft_max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

int		ft_min(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
