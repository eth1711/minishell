/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:31:04 by etlim             #+#    #+#             */
/*   Updated: 2024/07/01 17:52:41 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

void	ignore_sigint(int sig)
{
	(void)sig;
}

void	start_exec(t_cmd *head, t_env *envp)
{
	int				fds_pipe[3];

	fds_pipe[0] = FD_STDIN;
	fds_pipe[1] = FD_STDOUT;
	fds_pipe[2] = -1;
	signal(CTRL_C, ignore_sigint);
	if (head->type != PIPE)
		exec(head, envp, fds_pipe);
	else if (!fork())
	{
		exec(head, envp, fds_pipe);
		while (wait(&g_error) > 0)
			;
		exit(WEXITSTATUS(g_error));
	}
	if (wait(&g_error) > 0)
		g_error = WEXITSTATUS(g_error);
}

void	exec(t_cmd *head, t_env *envp, int *fds_pipe)
{
	if (head->type == EXEC)
		exec_execcmd((t_execcmd *)head, envp, fds_pipe);
	else if (head->type == REDIR)
		exec_redir((t_redircmd *)head, envp, fds_pipe);
	else if (head->type == PIPE)
		exec_pipe((t_pipecmd *)head, envp, fds_pipe);
}
