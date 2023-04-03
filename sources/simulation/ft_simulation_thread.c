/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_simulation_thread.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:27:31 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/04/03 11:17:45 by qbeukelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*ft_sim_thread(void *arg)
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
		if (ft_is_done(self) == TRUE)
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
		if (ft_set_are_done(philos_array, data, l_meal) == SUCCESS)
			return (FAILURE);
		if (ft_set_is_dead(data, l_meal) == SUCCESS)
		{
			ft_printf_died(&philos_array[i]);
			return (FAILURE);
		}
		usleep(50);
		i = (i + 1) % data->philo_nb;
	}
	return (-1);
}

static int	ft_set_are_done(t_philo *p_a, t_data *data, unsigned long l_meal)
{
	if (l_meal && ft_all_done(p_a, data) == TRUE)
	{
		ft_done(data);
		return (SUCCESS);
	}
	return (FAILURE);
}

static int	ft_all_done(t_philo *p_a, t_data *data)
{
	int		i;
	int		count_success;
	int		meals_count;

	if (data->must_eat == -1)
		return (FALSE);
	i = 0;
	count_success = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_lock(&p_a->data->mutex[MEALS]);
		meals_count = p_a[i].meal_counter;
		pthread_mutex_unlock(&p_a->data->mutex[MEALS]);
		if (meals_count >= data->must_eat)
			count_success++;
		i++;
	}
	if (count_success == (data->philo_nb))
		return (TRUE);
	return (FALSE);
}

void	ft_done(t_data *data)
{
	pthread_mutex_lock (&data->mutex[DONE]);
	data->done = TRUE;
	pthread_mutex_unlock (&data->mutex[DONE]);
}
