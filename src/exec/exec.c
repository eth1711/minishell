/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:31:04 by etlim             #+#    #+#             */
/*   Updated: 2024/06/03 15:53:19 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;
extern char	*g_pid;

void handler(int sig)
{
	(void)sig;
}

void	start_exec(t_cmd *head, t_env *envp)
{
	pid_t		pid;
	int				fds_pipe[3];
	
	fds_pipe[0] = dup(FD_STDIN);
	fds_pipe[1] = dup(FD_STDOUT);
	fds_pipe[2] = -1;
	signal(CTRL_C, handler);
	if (head->type != PIPE)
	{
		exec(head, envp, 0, fds_pipe);
		wait(0);
		return ;
	}
	pid = fork();
	if (!pid)
		exec(head, envp, 0, fds_pipe);
	waitpid(pid, &g_error, 0);
	while (wait(0) > 0)
		;
	close(fds_pipe[0]);
	close(fds_pipe[1]);
}

void	exec(t_cmd *head, t_env *envp, int forked, int *fds_pipe)
{
	if (head->type == EXEC)
		exec_execcmd((t_execcmd *)head, envp, forked, fds_pipe);
	else if (head->type == REDIR)
		exec_redir((t_redircmd *)head, envp, forked, fds_pipe);
	else if (head->type == PIPE)
		exec_pipe((t_pipecmd *)head, envp, fds_pipe);
}