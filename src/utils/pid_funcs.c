/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:01:33 by amaligno          #+#    #+#             */
/*   Updated: 2024/05/23 18:29:08 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pid(t_pid **head, t_pid *new)
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

t_pid	*new_pid(pid_t pid, t_pid *next)
{
	t_pid	*new;

	new = malloc(sizeof(t_pid));
	new->pid = pid;
	new->next = next;
	return (new);
}