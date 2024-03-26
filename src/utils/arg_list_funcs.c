/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:36:41 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/08 17:29:25 by amaligno         ###   ########.fr       */
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
