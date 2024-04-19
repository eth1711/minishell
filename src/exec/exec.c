/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:31:04 by etlim             #+#    #+#             */
/*   Updated: 2024/04/19 21:02:41 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

void	exec(t_cmd *head, t_env *envp)
{
	int		children;
	int		i;
	pid_t	*pids;

	i = 0;
	children = 0;
	pids = malloc(sizeof(pid_t) * 2);
	if (head->type == PIPE)
		children = exec_pipe((t_pipecmd *)head, envp, pids);
	else if (head->type == EXEC)
		children = exec_execcmd((t_execcmd *)head, envp, pids);
	else if (head->type == REDIR)
		children = exec_redir((t_redircmd *)head, envp, pids);
	while (i < children)
		waitpid(pids[i++], &g_error, 0);
	free(pids);
}
