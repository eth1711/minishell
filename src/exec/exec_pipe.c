/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:24:37 by amaligno          #+#    #+#             */
/*   Updated: 2024/05/27 20:55:18 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

void	exec_pipe(t_pipecmd *pipecmd, t_env *envp)
{
	int		fds[2];
	pid_t	pid;

	pipe(fds);
	pid = fork();
	if (!pid)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		exec(pipecmd->left, envp, 1);
	}
	pid = fork();
	if (!pid)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		exec(pipecmd->right, envp, 1);
	}
	close(fds[0]);
	close(fds[1]);
	wait(&g_error);
	wait(&g_error);
}
