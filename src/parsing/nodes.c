/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:45:55 by amaligno          #+#    #+#             */
/*   Updated: 2024/02/05 20:07:08 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Constructors for the token nodes

t_cmd	*pipecmd(t_cmd	*left, t_cmd *right)
{
	t_pipecmd	*pipe;

	pipe = malloc(sizeof(t_pipecmd));
	pipe->type = PIPE;
	pipe->left = left;
	pipe->right = right;
	return ((t_cmd *)pipe);
}

t_cmd	*redircmd(t_cmd *cmd, int fd, int mode, t_token filename)
{
	t_redircmd	*redir;

	redir = malloc(sizeof(t_redircmd));
	redir->cmd = cmd;
	redir->type = REDIR;
	redir->fd = fd;
	redir->mode = mode;
	redir->filename = filename.t;
	redir->efilename = filename.et;
	return ((t_cmd *)redir);
}

t_cmd	*execmd(int argc)
{
	t_execcmd	*exec;

	printf("execcmd: argc: %i\n", argc);
	exec = malloc(sizeof(t_execcmd));
	exec->type = EXEC;
	exec->argv = malloc(sizeof(char *) * (argc + 1));
	exec->eargv = malloc(sizeof(char *) * (argc + 1));
	exec->argv[argc] = NULL;
	exec->eargv[argc] = NULL;
	return ((t_cmd *)exec);
}
