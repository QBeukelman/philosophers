/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sim_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:59:49 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/04/03 10:48:37 by qbeukelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_print(t_philo *self, char *str)
{
	printf("%lu %d"
		" \e[1;34m%s\e[0m\n",
		ft_rel_time(self->data->sim_begin),
		self->id, str);
}

void	ft_printf_all_done(t_philo *self)
{
	printf("%lu \033[32;1m%s\033[0m",
		ft_rel_time(self->data->sim_begin),
		"All philosphoers done\n");
}

void	ft_printf_died(t_philo *self)
{
	printf ("%lu %d"
		" \033[31;1m%s\033[0m\n",
		ft_rel_time(self->data->sim_begin),
		self->id,
		"died");
}

void	ft_print_error(char *str)
{
	printf("\033[31;1m%s\033[0m\n", str);
}
