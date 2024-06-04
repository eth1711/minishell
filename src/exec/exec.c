/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:31:04 by etlim             #+#    #+#             */
/*   Updated: 2024/06/04 16:50:59 by amaligno         ###   ########.fr       */
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
	int				fds_pipe[3];
	
	fds_pipe[0] = dup(FD_STDIN);
	fds_pipe[1] = dup(FD_STDOUT);
	fds_pipe[2] = -1;
	signal(CTRL_C, handler);
	if (head->type != PIPE)
		exec(head, envp, 0, fds_pipe);
	else if (!fork())
	{
		exec(head, envp, 0, fds_pipe);
		while (wait(&g_error) > 0)
			;
		exit(WEXITSTATUS(g_error));
	}
	if (wait(&g_error) > 0)
		g_error = WEXITSTATUS(g_error);
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