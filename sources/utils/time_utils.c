/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:19:34 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/30 09:50:15 by quentinbeuk   ########   odam.nl         */
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
// This is because man usleep says that usleep will sleep at least n milliseconds
{
	unsigned long	abs_time;

	abs_time = ft_abs_time ();
	return (abs_time - begin);
}

void	ft_msleep(unsigned long msec)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    unsigned long start = tv.tv_sec * 1000000 + tv.tv_usec;
    unsigned long end = start + msec * 1000;

    while (1) {
        gettimeofday(&tv, NULL);
        unsigned long now = tv.tv_sec * 1000000 + tv.tv_usec;
        if (now >= end) break;
        usleep((end - now) / 1000);
    }
}
