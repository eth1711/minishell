/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:24:37 by amaligno          #+#    #+#             */
/*   Updated: 2024/05/27 21:21:41 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

void	exec_pipe(t_pipecmd *pipecmd, t_env *envp)
{
	int		fds[2];
	pid_t	pids[2];

	pipe(fds);
	pids[0] = fork();
	if (!pids[0])
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		exec(pipecmd->left, envp, 1);
	}
	pids[1] = fork();
	if (!pids[1])
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		exec(pipecmd->right, envp, 1);
	}
	close(fds[0]);
	close(fds[1]);
	waitpid(pids[0], &g_error, 0);
	waitpid(pids[1], &g_error, 0);
	exit(0);
}
