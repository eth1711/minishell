/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:24:37 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/24 10:30:24 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe(t_pipecmd *pipecmd, t_env *envp, pid_t *pids)
{
	int	fds[2];

	pipe(fds);
	pids[0] = fork();
	if (!pids[0])
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		if (pipecmd->left->type == REDIR)
			exec_redir((t_redircmd *)pipecmd->left, envp, NULL);
		else
			exec_execcmd((t_execcmd *)pipecmd->left, envp, NULL);
		exit(0);
	}
	pids[1] = fork();
	if (!pids[1])
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		exec(pipecmd->right, envp);
		exit(0);
	}
	close(fds[0]);
	close(fds[1]);
	return (2);
}
