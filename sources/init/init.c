/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 08:48:11 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/28 11:44:13 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// int		ft_init(int argc, char *argv[])
// {	

	
// 	data = malloc(sizeof(t_philo));
// 	if (data == NULL)
// 		return (FAILURE);
// 	data = ft_init_data(data, argc, argv);

// 	philos_array = malloc(sizeof(t_philo) * data->philo_nb);
// 	if (philos_array == NULL)
// 		return (FAILURE);
// 	philos_array = ft_init_philo(philos_array, data);

// 	return (SUCCESS);
// }

// ===== [ PHILO ] =====
t_philo		*ft_init_philo(t_philo *philos_array, t_data *data)
{
	int					i;
	pthread_mutex_t		*fork;

	fork = malloc(sizeof(pthread_mutex_t) * ((size_t)data->philo_nb));
	if (fork == NULL)
		return (NULL); // ! free

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}

	i = 0;
	while (i < data->philo_nb)
	{
		philos_array[i].last_meal = data->sim_begin;
		philos_array[i].id = i + 1;
		philos_array[i].last_meal = 0;
		philos_array[i].meal_counter = 0;
		philos_array[i].l_fork = i;
		if (i - 1 < 0)
			philos_array[i].r_fork = data->philo_nb - 1;
		else
			philos_array[i].r_fork = i - 1;
		philos_array[i].fork = fork;
		philos_array[i].data = data;
		i++;
	}
	return (philos_array);
}

// ===== [ DATA ] =====
t_data	*ft_init_data(t_data *data, int argc, char *argv[])
{
	data->sim_begin = ft_abs_time();
	data->philo_nb = (int)ft_atol(argv[1]);
	data->time_die = (int)ft_atol(argv[2]);
	data->time_eat = (int)ft_atol(argv[3]);
	data->time_sleep = (int)ft_atol(argv[4]);
	data->time_think = 0;
	if ((data->philo_nb % 2) && (data->time_eat > data->time_sleep))
		data->time_think = 1 + (data->time_eat - data->time_sleep);
	if (argc == 5)
		data->must_eat = -1;
	if (argc == 6)
		data->must_eat = (int)ft_atol(argv[5]);
	data->done = FALSE;
	data->died = FALSE;
	
	// init mutex
	data = ft_init_data_mutexes(data);

	return (data);
}

t_data		*ft_init_data_mutexes(t_data *data)
{
	int					i;
	pthread_mutex_t		*mutex;

	mutex = malloc (sizeof(pthread_mutex_t) * (size_t)data->philo_nb);
	if (mutex == NULL)
		return (NULL); // ! Free
	i = 0;
	while (i < data->philo_nb)
		pthread_mutex_init(&mutex[i++], NULL);
	data->mutex = mutex;
	
	
	return (data);
}
