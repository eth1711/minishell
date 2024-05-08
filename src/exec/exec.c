/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:31:04 by etlim             #+#    #+#             */
/*   Updated: 2024/05/08 17:22:49 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

void	free_children(t_pid *head)
{	
	t_pid	*ptr;

	while (head)
	{
		head = ptr->next;
		free(ptr);
	}
}

void	add_child(t_pid **head, t_pid *new)
{
	t_pid	*ptr;

	if (!head)
		return ;
	ptr = *head;
	if (!ptr)
	{
		*head = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

t_pid	*child(pid_t pid, pid_t *next)
{
	t_pid	*new;

	new = malloc(sizeof(t_pid));
	new->pid = pid;
	new->next = next;
	return (new);
}

void	exec(t_cmd *head, t_env *envp, t_pid **children)
{	
	t_pid	*ptr;
	
	if (!children)
		children = ptr;
	if (head->type == PIPE)
		exec_pipe((t_pipecmd *)head, envp, NULL);
	else if (head->type == EXEC)
		exec_execcmd((t_execcmd *)head, envp, NULL);
	else if (head->type == REDIR)
		exec_redir((t_redircmd *)head, envp, NULL);
	while (*children)
	{
		wait(&g_error);
		*children = (*children)->next;
	}
	free_children(children);
}
