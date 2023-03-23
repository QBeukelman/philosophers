/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_simulation.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:27:31 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/23 11:20:33 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void		*ft_simulation(void *arg)
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
		// Check died

		// Try to eat

		// Think

		// Sleep
	}

	// printf("ID: %d | %d %d | \n", self->id, self->l_fork, self->r_fork);
	if (self->id == 1)
	{

		// ft_print(self, "Thread created");
		pthread_mutex_lock(&self->fork[self->l_fork]);
		ft_print(self, "Picked up L_Fork");
		pthread_mutex_lock(&self->fork[self->r_fork]);
		ft_print(self, "Picked up R_Fork");
		sleep(3);
		pthread_mutex_unlock(&self->fork[self->l_fork]);
		ft_print(self, "Put down L_Fork");
		pthread_mutex_unlock(&self->fork[self->r_fork]);
		ft_print(self, "Put down R_Fork");
	}
	
	return (NULL);
}


