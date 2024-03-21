/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:50 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/21 15:32:21 by amaligno         ###   ########.fr       */
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
	init_signals();
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
			free_tree(tree);
			// system("leaks minishell");
			// if (tree->type == ERROR)
				// 
		}
		free(line);
		line = readline("minishell$ ");
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(0);
	return (0);
}
