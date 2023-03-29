/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sim_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:59:49 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/29 13:59:39 by qbeukelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_print(t_philo *self, char *str)
{
	printf("%lu %d"
		" \e[1;34m%s\e[0m\n", 
		ft_rel_time(self->data->sim_begin), 
		self->id, str);

	// printf("ID: %d, eaten: %d, must_eat: %d\n", self->id, self->meal_counter, self->data->must_eat);
}
