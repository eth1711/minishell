/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlim <etlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:33:24 by etlim             #+#    #+#             */
/*   Updated: 2024/07/09 18:56:07 by etlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

void	ft_unset(char **args_array, t_env *envp)
{
	t_env	*ptr;

	args_array++;
	while (!*args_array)
		break ;
	while (args_array && *args_array)
	{
		ptr = envp;
		while (ptr->next && ft_strcmp(ptr->key, *args_array))
			ptr = ptr->next;
		if (!ft_strcmp(ptr->key, *args_array))
		{
			if (ptr->next)
				ptr->next->prev = ptr->prev;
			if (ptr->prev)
				ptr->prev->next = ptr->next;
			free_2d((void *[4]){ptr->key, ptr->value, ptr, NULL});
		}
		args_array++;
	}
	g_error = 0;
}
