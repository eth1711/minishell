/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:25:37 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/20 15:49:22 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_cmd	*head)
{
	t_types	ptrs;

	if (!head)
		return ;
	if (head->type == ERROR)
		free_tree(((t_error *)head)->head);
	else if (head->type == PIPE)
	{
		ptrs.pipe = (t_pipecmd *)head;
		free_tree(ptrs.pipe->left);
		free_tree(ptrs.pipe->right);
	}
	else if (head->type == REDIR)
	{
		ptrs.redir = (t_redircmd *)head;
		free(ptrs.redir->filename);
		free_tree(ptrs.redir->cmd);
	}
	else if (head->type == EXEC)
	{
		ptrs.exec = (t_execcmd *)head;
		args_free(ptrs.exec->args_list);
		free(ptrs.exec->args_array);
	}
	free(head);
}

void	args_free(t_arg *head)
{
	if (!head)
		return ;
	free(head->s);
	if (head->next)
		args_free(head->next);
	free(head);
}

void	free_2d(void **array)
{
	while (*array)
		free(*array++);
}

void	free_env(t_env *head)
{
	t_env	*ptr;

	while (head)
	{
		free(head->key);
		free(head->value);
		ptr = head;
		head = head->next;
		free(ptr);
	}
}
