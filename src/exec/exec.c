/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:31:04 by etlim             #+#    #+#             */
/*   Updated: 2024/05/24 20:08:49 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

void	start_exec(t_cmd *head, t_env *envp)
{
	t_pid	*pids;
	t_pid	*ptr;

	pids = NULL;
	exec(head, envp, pids);
	while (pids)
	{
		waitpid(pids->pid, &g_error, 0);
		ptr = pids;
		pids = pids->next;
		free(ptr);
	}
}

void	exec(t_cmd *head, t_env *envp, t_pid **pids)
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
