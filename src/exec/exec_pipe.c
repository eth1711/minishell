/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:24:37 by amaligno          #+#    #+#             */
/*   Updated: 2024/05/08 17:21:22 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe(t_pipecmd *pipecmd, t_env *envp, int *io_fds /* pid_t *pids */)
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
		if (pipecmd->left->type == REDIR)
			exec_redir((t_redircmd *)pipecmd->left, envp, NULL);
		else
			exec_execcmd((t_execcmd *)pipecmd->left, envp, NULL);
		exit(0);
	}
	dup2(fds[0], STDIN_FILENO);
	close(fds[1]);
	close(fds[0]);
	exec(pipecmd->right, envp, io_fds);
	return (1);
}
