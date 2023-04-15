/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_exit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/07 12:58:45 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2023/04/15 21:27:48 by quentinbeuk   ########   odam.nl         */
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
	free (data);
	free (philos_array);
}

void	ft_exit(t_philo *philos_array, t_data *data, pthread_t *th)
{
	ft_destroy_mutexes(philos_array, data);
	(void)free (th);
	ft_free_structs(philos_array, data);
}
