/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:36:41 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/05 21:23:27 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_add_back(t_arg **head, t_arg *add)
{
	t_arg	*ptr;

	if (!add)
		return ;
	if (!*head)
	{
		*head = add;
		return ;
	}
	ptr = *head;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = add;
}

void	arg_add_front(t_arg **head, t_arg *add)
{
	if (!add)
		return ;
	if (!head)
	{
		*head = add;
		return ;
	}
	add->next = *head;
	*head = add;
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

t_arg	*arg_last(t_arg *head)
{
	if (!head)
		return (head);
	while (head->next)
		head = head->next;
	return (head);
}

int	arg_count(t_arg *head)
{
	int	i;

	i = 0;
	if (!head)
		return (i);
	while (head->next)
	{
		head = head->next;
		i++;
	}
	return (i);
}
