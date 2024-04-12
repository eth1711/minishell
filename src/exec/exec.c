/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:31:04 by etlim             #+#    #+#             */
/*   Updated: 2024/04/12 18:49:20 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_redir(t_redircmd *redir, t_env *envp)
{
	
}

void	exec_pipe(t_pipecmd *pipe, t_env *envp)
{
	
}

void	exec(t_cmd *head, t_env *envp)
{
	static int	children;

	if (head->type == PIPE)
	{
		exec_pipe((t_pipecmd *)head, envp);
		children += 2;
	}
	else if (head->type == EXEC)
		exec_cmd((t_execcmd *)head, envp);
	else if (head->type == REDIR)	
		exec_redir((t_redircmd *)head, envp);
	while (children)
	{
		wait(0);
		children--;
	}
}