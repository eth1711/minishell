/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:31:04 by etlim             #+#    #+#             */
/*   Updated: 2024/04/18 17:47:42 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

void	exec(t_cmd *head, t_env *envp)
{
	int	children;
	
	children = 0;
	if (head->type == PIPE)
	{
		exec_pipe((t_pipecmd *)head, envp);
		children += 2;
	}
	else if (head->type == EXEC)
	{
		exec_cmd((t_execcmd *)head, envp);
		children += 1;
	}
	else if (head->type == REDIR)
	{
		exec_redir((t_redircmd *)head, envp);
		children += 1;
	}
	while (children)
	{
		wait(&g_error);
		children--;
	}
}