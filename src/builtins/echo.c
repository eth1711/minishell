/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:38:27 by etlim             #+#    #+#             */
/*   Updated: 2024/07/01 18:43:03 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

void	ft_echo(char **args_array)
{
	int	flag;
	int	i;

	flag = 0;
	i = 2;
	args_array++;
	if (*args_array && (*args_array)[0] == '-' && (*args_array)[1] == 'n')
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
		if (++args_array && *args_array)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
	g_error = 0;
}
