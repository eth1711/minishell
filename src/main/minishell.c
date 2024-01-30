/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:50 by amaligno          #+#    #+#             */
/*   Updated: 2024/01/30 20:55:28 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	line = readline("minishell$ ");
	while (line)
	{
		add_history(line);
		if (line && *line)
		{
			if (!ft_strncmp(line, "cd", 2))
				cd_cmd(line);
			else
				parser(line, envp);
		}
		line = readline("minishell$ ");
	}
	exit(0);
	(void)envp;
	return (0);
}
