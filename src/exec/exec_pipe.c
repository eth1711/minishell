/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:24:37 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/19 16:04:16 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipe(t_pipecmd *pipecmd, t_env *envp)
{
	int	fds[2];
	int	pid;

	pid = fork();
	if (!pid)
	{
		dup2(fds[0], STDOUT_FILENO);
		if (pipecmd->left->type == REDIR)
			exec_redir((t_redircmd *)pipecmd->left, envp);
		else
			exec_execcmd((t_execcmd *)pipecmd->left, envp);
		exit(0);
	}
	pid = fork();
	if (!pid)
	{
		dup2(fds[1], STDIN_FILENO);
		exec(pipecmd->left, envp);
		exit(0);
	}
}
