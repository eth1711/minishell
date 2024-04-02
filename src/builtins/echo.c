/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlim <etlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:38:27 by etlim             #+#    #+#             */
/*   Updated: 2024/04/02 18:00:45 by etlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args_array)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (ft_strncmp(args_array[i], "-n", 2) == 0)
	{
		flag = 1;
		i++;
	}
	while (args_array[i])
	{
		ft_putstr_fd(args_array[i], 1);
		i++;
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
}
