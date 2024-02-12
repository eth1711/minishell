/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:50 by amaligno          #+#    #+#             */
/*   Updated: 2024/02/12 18:17:34 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(t_cmd	*cmd)
{
	t_error	*error;

	error = (t_error *)cmd;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*tree;

	(void)argc;
	(void)argv;
	line = readline("minishell$ ");
	while (line)
	{
		add_history(line);
		if (line && *line)
		{
			tree = praser(line);
			print_tree(tree);
			// if (tree->type == ERROR)
				// 
		}
		line = readline("minishell$ ");
	}
	exit(0);
	(void)envp;
	return (0);
}
