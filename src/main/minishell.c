/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:50 by amaligno          #+#    #+#             */
/*   Updated: 2024/07/09 13:40:39 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_error = 0;

static void	reset_fds(int startup)
{
	if (startup)
	{
		dup2(STDIN_FILENO, FD_STDIN);
		dup2(STDOUT_FILENO, FD_STDOUT);
		return ;
	}
	dup2(FD_STDIN, STDIN_FILENO);
	dup2(FD_STDOUT, STDOUT_FILENO);
}

static void	init(t_env **envp_list, char **envp, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	init_signals();
	reset_fds(1);
	*envp_list = env_to_list(envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*tree;
	t_env	*envp_list;

	init(&envp_list, envp, argc, argv);
	line = readline("minishell$ ");
	while (line)
	{
		add_history(line);
		if (line && *line)
		{
			tree = parser(line, envp_list);
			if (tree && tree->type != ERROR)
				start_exec(tree, envp_list);
			init_signals();
			reset_fds(0);
			free_tree(tree);
		}
		free(line);
		line = readline("minishell$ ");
	}
	system("leaks minishell");
	free(line);
	clear_history();
	free_env(envp_list);
	ft_putstr_fd("exit\n", STDERR_FILENO);
}
