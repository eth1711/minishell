/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:19:24 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/05 16:45:56 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(char **new, char *env)
{
	char	c;
	int		count;
	
	
}

void	expansion(char *t, char *et, t_execcmd *exec, t_env *env)
{
	char	*new;
	int		count;

	count = 0;
	new = ft_strdup("");
	while ((t + count) < et)
	{
		while ((t + count) < et && !ft_strchr("\'\"$", t[count]))
			count++;
		new = ft_strjoin(new, ft_substr(t, 0, count));
		t += count;
		if ((t + count) < et && ft_strchr("\'\"$", t[count]))
			expand(&new, env);
		count = 0;
	}
	arg_add_back(&exec->args_list, args(new, et, 1));
}