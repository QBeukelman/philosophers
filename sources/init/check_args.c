/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 10:58:31 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/03/20 09:47:44 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

bool	ft_is_numberic(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '\0')
		return (TRUE);
	return (FALSE);
}

int		ft_check_args(int argc, char *argv[])
{
	// Check arg count
	if (argc < 5)
	{
		write (2, "Error: Too few arguments.\n", 26);
		return (FAILURE);
	}
	if (argc > 6)
	{
		write (2, "Error: Too many arguments.\n", 27);
		return (FAILURE);
	}
	
	while (argc-- > 1)
	{
		if (ft_is_numberic(argv[argc]) == FALSE)
		{
			write (2, "Error: Invalid character.\n", 26);
			return (FAILURE);
		}
		if (ft_stol(argv[argc]) > INT_MAX || ft_stol(argv[argc]) < 0)
		{
			write (2, "Error: Value out of range.\n", 27);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
