/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 10:58:31 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/04/17 09:11:28 by qbeukelm      ########   odam.nl         */
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

int	ft_check_args(int argc, char *argv[])
{
	if (ft_check_args_helper(argc, argv) != SUCCESS)
		return (FAILURE);
	while (argc-- > 1)
	{
		if (ft_is_numberic(argv[argc]) == FALSE)
		{
			ft_print_error("Error: Invalid character.");
			return (FAILURE);
		}
		if (ft_atol(argv[argc]) > INT_MAX || ft_atol(argv[argc]) < 0)
		{
			ft_print_error("Error: Value out of range.");
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	ft_check_args_helper(int argc, char *argv[])
{
	if (argc < 5)
	{
		ft_print_error("Error: Too few arguments.");
		return (FAILURE);
	}
	if (argc > 6)
	{
		ft_print_error("Error: Too many arguments.");
		return (FAILURE);
	}
	if (argc == 6)
	{
		if ((int)ft_atol(argv[5]) == 0)
		{
			ft_print_error("Error: Must eat may not be 0.");
			return (FAILURE);
		}
	}
	if ((int)ft_atol(argv[1]) == 1)
	{
		ft_one_philo(argv);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	ft_one_philo(char *argv[])
{
	ft_msleep((int)ft_atol(argv[2]));
	printf ("%d %d"
		" \033[31;1m%s\033[0m\n",
		(int)ft_atol(argv[2]),
		1,
		"died");
}
