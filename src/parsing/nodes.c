/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:45:55 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/24 08:27:19 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Constructors for the token nodes

t_cmd	*pipecmd(t_cmd	*left, t_cmd *right)
{
	t_pipecmd	*pipe;

	if (!left || right)
		return (NULL);
	pipe = malloc(sizeof(t_pipecmd));
	pipe->type = PIPE;
	pipe->left = left;
	pipe->right = right;
	return ((t_cmd *)pipe);
}

t_cmd	*redircmd(t_cmd *cmd, int fd, int mode, char *filename)
{
	t_redircmd	*redir;

	redir = malloc(sizeof(t_redircmd));
	redir->cmd = cmd;
	redir->type = REDIR;
	redir->fd = fd;
	redir->mode = mode;
	redir->filename = filename;
	return ((t_cmd *)redir);
}

t_arg	*args(char *s, t_arg *next)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	arg->s = s;
	arg->next = next;
	return (arg);
}

t_cmd	*execcmd(void)
{
	t_execcmd	*exec;

	exec = malloc(sizeof(t_execcmd));
	exec->type = EXEC;
	exec->args_array = NULL;
	exec->args_list = NULL;
	return ((t_cmd *)exec);
}

t_cmd	*error(t_cmd *head, char *err_msg)
{
	t_error	*error;

	error = malloc(sizeof(t_error));
	if (err_msg)
		ft_putstr_fd(err_msg, STDERR_FILENO);
	error->type = ERROR;
	error->head = head;
	return ((t_cmd *)error);
}
