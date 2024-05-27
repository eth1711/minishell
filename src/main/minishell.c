/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:50 by amaligno          #+#    #+#             */
/*   Updated: 2024/05/27 19:13:37 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_error = 0;
char	*g_pid = NULL;

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*tree;
	t_env	*envp_list;

	(void)argc;
	(void)argv;
	init_signals();
	envp_list = env_to_list(envp);
	line = readline("minishell$ ");
	while (line)
	{
		add_history(line);
		if (line && *line)
		{
			tree = parser(line, envp_list);
			print_tree(tree);
			free(line);
			if (tree && tree->type != ERROR)
				start_exec(tree, envp_list);
			init_signals();
			free_tree(tree);
		}
		// system("leaks minishell");
		line = readline("minishell$ ");
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	// system("leaks minishell");
	rl_clear_history();
	exit(0);
	return (0);
}
