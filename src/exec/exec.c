/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:31:04 by etlim             #+#    #+#             */
/*   Updated: 2024/04/02 15:48:40 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_cmd(t_redircmd *redir, t_env *envp)
{
	
}

void	exec_cmd(t_execcmd *exec, t_env *envp)
{
	if (is_builtin(exec->args_array, envp))
		return ;
	
}

void	exec_pipe(t_pipecmd *pipe, t_env *envp)
{
	
}

void	exec(t_cmd *head, t_env *envp)
{
	if (head->type == PIPE)
		exec_pipe((t_pipecmd *)head, envp);
	else if (head->type == EXEC)
		exec_cmd((t_execcmd *)head, envp);
	else if (head->type == REDIR)	
		exec_redir((t_redircmd *)head, envp);
}
