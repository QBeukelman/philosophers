/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:58:45 by quentinbeuk       #+#    #+#             */
/*   Updated: 2024/10/04 15:21:01 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_destroy_mutexes(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_nb)
		pthread_mutex_destroy (&philo->fork[i++]);
	i = 0;
	while (i < M_NUM)
		pthread_mutex_destroy (&data->mutex[i++]);
}

void	ft_free_structs(t_philo *philos_array, t_data *data)
{
	free (data->mutex);
	free (data);
	free (philos_array->fork);
	free (philos_array);
}

int	ft_exit(t_philo *philos_array, t_data *data)
{
	ft_destroy_mutexes(philos_array, data);
	ft_free_structs(philos_array, data);
	return (SUCCESS);
}

// ===== [ EXIT INIT ] =====
int	ft_exit_init(t_philo **philos_array, t_data **data)
{
	int	i;

	if (*data != NULL)
	{
		i = 0;
		while (i < M_NUM)
			pthread_mutex_destroy (&(*data)->mutex[i++]);
		free (data);
	}
	if (*philos_array != NULL)
	{
		i = 0;
		while (i < (*philos_array)->data->philo_nb)
			pthread_mutex_destroy (&(*philos_array)->fork[i++]);
		free (philos_array);
	}
	return (SUCCESS);
}
