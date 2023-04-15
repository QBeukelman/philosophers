/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 08:48:11 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/04/15 21:21:24 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// ===== [ PHILO ] =====
int	ft_init_philo(t_philo **philos_array, t_data *data)
{
	int					i;
	pthread_mutex_t		*fork;

	fork = malloc(sizeof(pthread_mutex_t) * ((size_t)data->philo_nb));
	if (fork == NULL)
	{
		ft_print_error("ERROR: Not enough memory to perform malloc().");
		return (FAILURE);
	}
	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	ft_init_helper(philos_array, data, fork);
	return (SUCCESS);
}

int	ft_init_helper(t_philo **p_a, t_data *data, pthread_mutex_t *fork)
{
	int					i;

	i = 0;
	while (i < data->philo_nb)
	{
		(*p_a)[i].last_meal = data->sim_begin;
		(*p_a)[i].id = i + 1;
		(*p_a)[i].meal_counter = 0;
		(*p_a)[i].l_fork = i;
		if (i - 1 < 0)
			(*p_a)[i].r_fork = data->philo_nb - 1;
		else
			(*p_a)[i].r_fork = i - 1;
		(*p_a)[i].fork = fork;
		(*p_a)[i].data = data;
		i++;
	}
	return (SUCCESS);
}

// ===== [ DATA ] =====
int	ft_init_data(t_data **data, int argc, char *argv[])
{
	(*data)->sim_begin = ft_abs_time();
	(*data)->philo_nb = (int)ft_atol(argv[1]);
	(*data)->time_die = (int)ft_atol(argv[2]);
	(*data)->time_eat = (int)ft_atol(argv[3]);
	(*data)->time_sleep = (int)ft_atol(argv[4]);
	(*data)->time_think = 0;
	if (((*data)->philo_nb % 2) && ((*data)->time_eat > (*data)->time_sleep))
		(*data)->time_think = 1 + ((*data)->time_eat - (*data)->time_sleep);
	if (argc == 5)
		(*data)->must_eat = -1;
	if (argc == 6)
		(*data)->must_eat = (int)ft_atol(argv[5]);
	(*data)->done = FALSE;
	(*data)->died = FALSE;
	
	ft_init_data_mutexes(data);

	return (SUCCESS);
}

// ===== [ MUTEX ] =====
int	ft_init_data_mutexes(t_data **data)
{
	int					i;
	pthread_mutex_t		*mutex;

	mutex = malloc (sizeof(pthread_mutex_t) * (size_t)M_NUM);
	if (mutex == NULL)
	{
		ft_print_error("ERROR: Not enough memory to perform malloc().");
		return (FAILURE); // ! Catch NULL
	}
	i = 0;
	while (i < M_NUM)
		pthread_mutex_init (&mutex[i++], NULL);
	(*data)->mutex = mutex;
	return (SUCCESS);
}

// ===== [ INIT ] =====
int		ft_init(t_philo **philos_array, t_data **data, int argc, char *argv[])
{
	*data = (t_data *)malloc (sizeof (t_data));
	if (*data == NULL)
		return (FAILURE);
	(*data)->mutex = NULL;
	if (ft_init_data(data, argc, argv) != SUCCESS)
		return (FAILURE);
	*philos_array = (t_philo *)malloc (sizeof (t_philo) * (size_t)(*data)->philo_nb);
	if (*philos_array == NULL)
		return (FAILURE);
	(*philos_array)->fork = NULL;
	if (ft_init_philo (philos_array, *data) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
