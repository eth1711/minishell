/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/01 17:57:32 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

int	count_args(char *args_array)
{
	int	i;

	i = 0;
	while (args_array[i] && ft_isdigit(args_array[i]))
		i++;
	if (args_array[i])
		return (1);
	return (0);
}

void	ft_exit(char **args_array)
{
	args_array++;
	if (*args_array && *(args_array + 1))
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_error = 1;
		return ;
	}
	else if (*args_array)
	{
		if (count_args(*args_array) && *args_array)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(*args_array, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit(255);
		}
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(ft_atoi(*args_array));
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(0);
}
