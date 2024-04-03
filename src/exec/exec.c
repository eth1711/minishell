/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:31:04 by etlim             #+#    #+#             */
/*   Updated: 2024/04/03 17:08:03 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_redir(t_redircmd *redir, t_env *envp)
{
	
}

void	exec_execcmd(t_execcmd *exec, t_env *envp)
{
	int		pid;
	int		ret;
	char	**envp_array;

	if (is_builtin(exec->args_array, envp))
		return ;
	pid = fork();
	if (!pid)
	{
		ret = execve();
		exit(ret);
	}
	wait()
			
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