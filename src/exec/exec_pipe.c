/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:24:37 by amaligno          #+#    #+#             */
/*   Updated: 2024/05/24 18:01:26 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipe(t_pipecmd *pipecmd, t_env *envp, t_pid **pids)
{
	int		fds[2];
	t_pid	*pid;

	pipe(fds);
	pid = new_pid(fork(), NULL);
	if (!pid->pid)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		if (pipecmd->left->type == REDIR)
			exec_redir((t_redircmd *)pipecmd->left, envp, pids);
		else if (pipecmd->left->type == EXEC)
			exec_execcmd((t_execcmd *)pipecmd->left, envp, pids);
	}
	add_pid(pids, pid);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	close(fds[1]);
	exec(pipecmd->right, envp, pids);
}
