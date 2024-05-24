/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:50 by amaligno          #+#    #+#             */
/*   Updated: 2024/05/23 18:28:31 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error = 0;

void	reset_fds(int *fds)
{
	dup2(fds[0], STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
}

void	save_fds(int **fds)
{
	*fds = malloc(sizeof(int) * 2);
	(*fds)[0] = dup(STDIN_FILENO);
	(*fds)[1] = dup(STDOUT_FILENO);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		*io_fds;
	t_cmd	*tree;
	t_env	*envp_list;

	(void)argc;
	(void)argv;
	save_fds(&io_fds);
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
			reset_fds(io_fds);
			free_tree(tree);
		}
		// system("leaks minishell");
		line = readline("minishell$ ");
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	// system("sudo leaks minishell");
	rl_clear_history();
	exit(0);
	return (0);
}
