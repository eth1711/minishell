/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:31:04 by etlim             #+#    #+#             */
/*   Updated: 2024/05/27 16:55:01 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

void	start_exec(t_cmd *head, t_env *envp)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
		exec(head, envp);
	wait(0);
}

void	exec(t_cmd *head, t_env *envp)
{
	if (head->type == EXEC)
		exec_execcmd((t_execcmd *)head, envp);
	else if (head->type == PIPE)
		exec_pipe((t_pipecmd *)head, envp);
	else if (head->type == REDIR)
		exec_redir((t_redircmd *)head, envp);
	exit(0);
}
