/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:50 by amaligno          #+#    #+#             */
/*   Updated: 2024/07/10 00:57:43 by amaligno         ###   ########.fr       */
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
		dup2(STDERR_FILENO, STDOUT_FILENO);
		return ;
	}
	dup2(FD_STDIN, STDIN_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
}

static void	init(t_env **envp_list, char **envp, int argc, char **argv)
{
	int		i_lvl;
	char	*s_lvl;

	(void)argc;
	(void)argv;
	reset_fds(1);
	init_signals();
	*envp_list = env_to_list(envp);
	s_lvl = get_env("SHLVL", *envp_list);
	i_lvl = ft_atoi(s_lvl);
	s_lvl = ft_itoa(i_lvl + 1);
	put_env("SHLVL", s_lvl, envp_list);
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
	free_env(envp_list);
	free(line);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	return (g_error);
}
