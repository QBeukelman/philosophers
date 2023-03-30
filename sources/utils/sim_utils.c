/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sim_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:59:49 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/30 11:47:29 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_print(t_philo *self, char *str)
{
	printf("%lu %d"
		" \e[1;34m%s\e[0m\n", 
		ft_rel_time(self->data->sim_begin), 
		self->id, str);

	// printf("ID: %d,		meals: %d,		must_eat: %d\n", self->id, self->meal_counter, self->data->must_eat);
}
