/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:38:27 by etlim             #+#    #+#             */
/*   Updated: 2024/06/23 22:41:55 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args_array)
{
	int	flag;
	int	i;

	flag = 0;
	i = 2;
	args_array++;
	if (args_array && (*args_array)[0] == '-' && (*args_array)[1] == 'n')
	{
		while ((*args_array)[i] == 'n')
			i++;
		if (!(*args_array)[i])
		{
			flag = 1;
			args_array++;
		}
	}
	while (args_array && *args_array && **args_array)
	{
		ft_putstr_fd(*args_array, STDOUT_FILENO);
		args_array++;
		if (args_array && *args_array)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
}
