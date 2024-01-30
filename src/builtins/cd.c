/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:11:06 by amaligno          #+#    #+#             */
/*   Updated: 2024/01/30 18:11:27 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_cmd(char *line)
{
	if (ft_strlen(line) > 3)
	{
		line[2] = '\0';
		if (chdir(line + 3) < 0)
			ft_putstr_fd("Cannot cd :( \n", 2);
	}
	else
		chdir("~");
}
