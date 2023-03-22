/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_simulator.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:27:07 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/22 12:11:55 by qbeukelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int		ft_simulator(t_philo *philos_array, t_data *data)
{
	int			i;
	pthread_t	*th;

	th = malloc (sizeof (pthread_t) * (size_t)data->philo_nb);
	if (th == NULL)
		return (FAILURE);


	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create (&th[i], 0, ft_simulation, (void *)&philos_array[i]))
		{
			while (i >= 0)
			{
				pthread_join (th[i], NULL);
				i--;
			}
			(void)free (th);
			return (FAILURE);
		}
		i++;
	}

	if (ft_monitor (philos_array, data) != SUCCESS)
	{
		(void)ft_destroy_mutexes (philos_array, data);
		(void)free(th);
		return (FAILURE);
	}

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join (th[i], NULL))
			return (FAILURE);
		i++;
	}

	(void)ft_destroy_mutexes(philos_array, data);
	(void)free (th);

	return (SUCCESS);
}

static int	ft_monitor(t_philo *philo, t_data *data)
{
	int				i;
	unsigned long	l_meal;

	i = 0;
	while (1)
	{
		pthread_mutex_lock (&data->mutex[MEALS]);
		l_meal = philo[i].last_meal;
		pthread_mutex_unlock (&data->mutex[MEALS]);
		if (l_meal && ft_all_done (philo, data))
		{
			ft_done (data);
			break ;
		}
		if (l_meal && ft_abs_time () - l_meal > (unsigned long)data->time_die)
		{
			ft_died (data);
			ft_print (&philo[i], "died");
			break ;
		}
		i = (i + 1) % data->philo_nb;
		usleep (200);
	}
	return (SUCCESS);
}

static int		ft_all_done(t_philo *philos_array, t_data *data)
{
	int		i;
	int		done;
	int		meals_count;

	if (data->must_eat == -1)
		return (FALSE);
	
	i = 0;
	done = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_lock(&data->mutex[MEALS]);
		meals_count = philos_array[i].meal_counter;
		pthread_mutex_unlock(&data->mutex[MEALS]);
		if (meals_count < data->must_eat)
			return (FALSE);
		done++;
		i++;
	}
	if (done == data->philo_nb)
		return (TRUE);
	return (FALSE);
}

static void		ft_destroy_mutexes(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_nb)
		pthread_mutex_destroy (&philo->fork[i++]);
	i = 0;
	while (i < M_NUM)
		pthread_mutex_destroy (&data->mutex[i++]);
}
