/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:50 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/14 19:36:10 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*tree;
	t_env	*envp_list;

	(void)argc;
	(void)argv;
	envp_list = init_envp(envp);
	print_env(envp_list);
	line = readline("minishell$ ");
	while (line)
	{
		add_history(line);
		if (line && *line)
		{
			tree = parser(line, envp_list);
			print_tree(tree);
			// if (tree->type == ERROR)
				// 
		}
		free(line);
		line = readline("minishell$ ");
	}
	exit(0);
	return (0);
}
