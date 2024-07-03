/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:43:24 by amaligno          #+#    #+#             */
/*   Updated: 2024/07/03 16:12:19 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_tokens(t_execcmd *exec, char	**new)
{
	char	**split;
	int		i;

	i = 0;
	if (!ft_strchr(*new, ' '))
		return ;
	split = ft_split(*new, ' ');
	while (split[i] && split[i + 1])
	{
		arg_add_back(&exec->args_list, args(split[i], NULL));
		i++;
	}
	free(*new);
	*new = split[i];
	free(split);
}

char	*ft_safejoin(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	if (tmp)
		free(tmp);
	if (s2)
		free(s2);
	return (s1);
}
