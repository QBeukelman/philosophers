/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sim_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:59:49 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/23 13:55:59 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_print(t_philo *philos_array, char *str)
{
	printf("%lu %d"
		" \e[1;34m%s\e[0m\n", 
		ft_rel_time(philos_array->data->sim_begin), 
		philos_array->id, str);
}
