/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_simulation_thread.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:27:31 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/31 08:56:44 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void		*ft_simulation_thread(void *arg)
{
	t_philo		*self;

	self = (t_philo *)arg;

	if (self->id % 2 == 0)
	{
		ft_print(self, "is thinking");
		ft_msleep(self->data->time_eat);
	}

	while (1)
	{
		if (ft_check_die(self) == TRUE)
			break ;
		if (ft_eating(self) != SUCCESS)
			break ;
		if (ft_sleep(self) == SUCCESS)
			ft_think(self);
	}
	
	return (NULL);
}

// ===== [ observe ] =====
int			ft_observe_thread(t_philo *philos_array, t_data *data)
{
	int				i;
	unsigned long	l_meal;
	
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mutex[MEALS]);
		l_meal = philos_array[i].last_meal;
		pthread_mutex_unlock(&data->mutex[MEALS]);

		if (ft_set_are_done(philos_array, data, l_meal) == SUCCESS)
		{
			return (printf("ALL PHILOS DONE\n"), FAILURE); // ! All philos done
		}
		if (ft_set_is_dead(data, l_meal) == SUCCESS)
		{
			ft_print (&philos_array[i], "died");
			return (FAILURE); // ! Philo dies
		}
		i = (i + 1) % data->philo_nb;
		usleep(50);
	}

	return (SUCCESS);
}

static int	ft_set_are_done(t_philo *p_a, t_data *data, unsigned long l_meal)
{
	if (l_meal && ft_all_done(p_a, data) == TRUE)
	{
		ft_done(data); // ! Destroy threads
		return (SUCCESS); // ! All philos done
	}

	return (FAILURE);
}

static int	ft_all_done(t_philo *p_a, t_data *data)
{
	int		i;
	int		count_success;
	int		meals_count;

	if (data->must_eat == -1)
		return (printf("ft_all_done(), must_eat == -1\n"), FAILURE);

	i = 0;
	count_success = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_lock(&p_a->data->mutex[MEALS]);
		meals_count = p_a[i].meal_counter;
		pthread_mutex_unlock(&p_a->data->mutex[MEALS]);
	
		if (meals_count == data->must_eat)
			count_success++;
		usleep(50);
		i++;
	}
	if (count_success == (data->philo_nb - 1))
		return (TRUE);
	return (FALSE);
}

void	ft_done(t_data *data)
{
	pthread_mutex_lock (&data->mutex[DONE]);
	data->done = TRUE;
	pthread_mutex_unlock (&data->mutex[DONE]);
}

// ===== [ died ] =====
static int	ft_set_is_dead(t_data *data, unsigned long l_meal)
{
	if (l_meal && (ft_abs_time() - l_meal) > (unsigned long)data->time_die)
	{
		ft_died(data); // ! Destroy threads
		return (SUCCESS);
	}
	return (FAILURE);
}

void	ft_died(t_data *data)
{
	pthread_mutex_lock (&data->mutex[DIED]);
	data->died = TRUE;
	pthread_mutex_unlock (&data->mutex[DIED]);
}

int		ft_check_die(t_philo *self)
{
	pthread_mutex_lock(&self->data->mutex[DIED]);
	if (self->data->died == TRUE)
	{
		return (TRUE);
	}
	pthread_mutex_unlock(&self->data->mutex[DIED]);
	return (FALSE);
}
