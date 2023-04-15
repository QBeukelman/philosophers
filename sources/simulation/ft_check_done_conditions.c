/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_check_done_conditions.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 11:15:14 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/04/15 20:09:24 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// ===== [ all done ] =====
int	ft_all_done(t_philo *p_a, t_data *data)
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
		usleep(50);
		i++;
	}
	if (count_success == (data->philo_nb))
		return (TRUE);
	return (FALSE);
}

// ===== [ is done ] =====
int	ft_is_done(t_philo *self)
{
	pthread_mutex_lock(&self->data->mutex[DONE]);
	if (self->data->done)
	{
		pthread_mutex_unlock(&self->data->mutex[DONE]);
		return (TRUE);
	}
	pthread_mutex_unlock(&self->data->mutex[DONE]);
	return (FALSE);
}

// ===== [ done ] =====
void	ft_done(t_data *data)
{
	pthread_mutex_lock (&data->mutex[DONE]);
	data->done = TRUE;
	pthread_mutex_unlock (&data->mutex[DONE]);
}

// ===== [ fork selection ] =====
int	ft_max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
