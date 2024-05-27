/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:31:04 by etlim             #+#    #+#             */
/*   Updated: 2024/05/27 20:54:29 by amaligno         ###   ########.fr       */
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

	if (head->type != PIPE)
	{
		exec(head, envp, 0);
		return ;
	}
	pid = fork();
	if (!pid)
	{
		exec(head, envp, 1);
		signal(CTRL_C, handler);
		waitpid(pid, &g_error, 0);
	}
}

void	exec(t_cmd *head, t_env *envp, int forked)
{
	if (head->type == EXEC)
		exec_execcmd((t_execcmd *)head, envp, forked);
	else if (head->type == REDIR)
		exec_redir((t_redircmd *)head, envp, forked);
	else if (head->type == PIPE)
		exec_pipe((t_pipecmd *)head, envp);
}
