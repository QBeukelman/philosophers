/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:19:34 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/04/03 10:47:56 by qbeukelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

unsigned long	ft_abs_time(void)
{
	struct timeval		time;
	unsigned long		s;
	unsigned long		u;

	if (gettimeofday(&time, NULL) == -1)
		write (2, "ERROR: gettimeofday(2).\n", 24);
	s = time.tv_sec * 1000;
	u = time.tv_usec / 1000;
	return (s + u);
}

unsigned long	ft_rel_time(unsigned long begin)
{
	unsigned long	abs_time;

	abs_time = ft_abs_time ();
	return (abs_time - begin);
}

void	ft_msleep(unsigned long msec)
/* This is because man usleep says that usleep
will sleep at least n milliseconds */
{
	struct timeval	tv;
	unsigned long	start;
	unsigned long	end;
	unsigned long	now;

	gettimeofday(&tv, NULL);
	start = tv.tv_sec * 1000000 + tv.tv_usec;
	end = start + msec * 1000;
	while (1)
	{
		gettimeofday(&tv, NULL);
		now = tv.tv_sec * 1000000 + tv.tv_usec;
		if (now >= end)
			break ;
		usleep((end - now) / 1000);
	}
}
