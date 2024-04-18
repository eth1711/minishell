/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:47:27 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/18 18:17:14 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc()
{
	
}

void	exec_redir(t_redircmd *redir, t_env *envp)
{
	int	fd;

	if (redir->mode == LL)
	{
		
	}
	else
	{
		fd = open(redir->filename, redir->mode);
		dup2(fd, redir->fd);
		close(fd);
	}
	exec_execcmd(redir->cmd, envp);
}
