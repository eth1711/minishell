/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:24:37 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/22 10:06:38 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe(t_pipecmd *pipecmd, t_env *envp, pid_t *pids)
{
	int	fds[2];
	int	pid;

	pipe(fds);
	pid = fork();
	pids[0] = pid;
	if (!pid)
	{
		dup2(fds[0], STDOUT_FILENO);
		if (pipecmd->left->type == REDIR)
			exec_redir((t_redircmd *)pipecmd->left, envp, NULL);
		else
			exec_execcmd((t_execcmd *)pipecmd->left, envp, NULL);
		exit(0);
	}
	pid = fork();
	pids[1] = pid;
	if (!pid)
	{
		dup2(fds[1], STDIN_FILENO);
		exec(pipecmd->right, envp);
		exit(0);
	}
	return (2);
}
