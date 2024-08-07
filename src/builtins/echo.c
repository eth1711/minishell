/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlim <etlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:38:27 by etlim             #+#    #+#             */
/*   Updated: 2024/07/10 15:59:02 by etlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

void	ft_echo(char **args_array)
{
	int	flag;
	int	i;

	args_array++;
	i = 0;
	flag = 0;
	while (*args_array && (*args_array)[i] == '-' && (*args_array)[++i] == 'n')
	{
		while ((*args_array)[++i] == 'n')
			i++;
		if (!(*args_array)[i])
		{
			flag = 1;
			args_array++;
			i = 0;
		}
	}
	while (*args_array)
	{
		ft_putstr_fd(*args_array, STDOUT_FILENO);
		if (++args_array && *args_array)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flag == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
