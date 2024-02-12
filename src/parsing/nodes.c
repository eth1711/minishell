/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:45:55 by amaligno          #+#    #+#             */
/*   Updated: 2024/02/12 17:40:04 by amaligno         ###   ########.fr       */
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

t_cmd	*redircmd(t_cmd *cmd, int fd, int mode, t_strptrs filename)
{
	t_redircmd	*redir;

	redir = malloc(sizeof(t_redircmd));
	redir->cmd = cmd;
	redir->type = REDIR;
	redir->fd = fd;
	redir->mode = mode;
	redir->filename = filename.s;
	redir->efilename = filename.es;
	return ((t_cmd *)redir);
}

t_arg	*args(char *s, char *es, bool is_malloced)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	arg->is_malloced = is_malloced;
	arg->s = s;
	arg->es = es;
	arg->next = NULL;
	return (arg);
}

t_cmd	*execmd(void)
{
	t_execcmd	*exec;

	exec = malloc(sizeof(t_execcmd));
	exec->type = EXEC;
	exec->args_array = NULL;
	exec->args_list = NULL;
	return ((t_cmd *)exec);
}

t_cmd	*error(t_cmd *head, char *message)
{
	t_error	*error;

	error = malloc(sizeof(t_error));
	error->type = ERROR;
	error->error_msg = ft_strdup(message);
	error->head = head;
	return ((t_cmd *)error);
}
