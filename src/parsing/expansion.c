/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:19:24 by amaligno          #+#    #+#             */
/*   Updated: 2024/02/19 17:54:19 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env(char *new, char *env)
{
	
}

void	expansion(char *t, char *et, t_execcmd *exec)
{
	char	*new;
	int		count;

	count = 0;
	while ((t + count) < et)
	{
		while ((t + count) < et && t[count] != '$')
			count++;
		if (t[count] == '$')
			new = expand_env(new, t);
	}
	arg_add_back(&exec->args_list, args(new, et, 1));
}