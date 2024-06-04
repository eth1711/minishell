/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:45:55 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/04 17:51:31 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

//Constructors for the token nodes

t_cmd	*pipecmd(t_cmd	*left, t_cmd *right)
{
	t_pipecmd	*pipe;

	if (!left || !right)
		return (NULL);
	pipe = malloc(sizeof(t_pipecmd));
	pipe->type = PIPE;
	pipe->left = left;
	pipe->right = right;
	return ((t_cmd *)pipe);
}

//This conrtuctor node adds the given command to the last node if it is a redir
//this is to correctly built the tree for redir during execution
t_cmd	*redircmd(t_cmd *cmd, int fd, int mode, char *filename)
{
	t_redircmd	*redir;
	t_redircmd	*ptr;
	t_cmd		*exec;

	redir = malloc(sizeof(t_redircmd));
	redir->type = REDIR;
	redir->fd = fd;
	redir->mode = mode;
	redir->filename = filename;
	if (cmd->type == REDIR)
	{
		ptr = (t_redircmd *)cmd;
		while (ptr && ptr->cmd->type == REDIR)
		{
			ptr = (t_redircmd *)ptr->cmd;
		}
		exec = ptr->cmd;
		ptr->cmd = (t_cmd *)redir;
		redir->cmd = exec;
		return (cmd);
	}
	redir->cmd = cmd;
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

t_cmd	*error(t_cmd *head, char *err_msg, int error_number)
{
	t_error	*error;

	error = malloc(sizeof(t_error));
	if (err_msg)
		ft_putstr_fd(err_msg, STDERR_FILENO);
	error->type = ERROR;
	error->head = head;
	g_error = error_number;
	return ((t_cmd *)error);
}
