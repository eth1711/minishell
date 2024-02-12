/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:19:24 by amaligno          #+#    #+#             */
/*   Updated: 2024/02/12 17:38:28 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expansion(char *t, char *et, t_execcmd *exec)
{
	char	*s;

	s = t;
	if (*t == '\'')
	{
		arg_add_back(&exec->args_list, args(++t, et, 0));
		return ;
	}
	while (checktoken(&s, et, "$"))
	{
		
	}
}