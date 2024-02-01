/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:01:10 by amaligno          #+#    #+#             */
/*   Updated: 2024/02/01 21:53:11 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gettoken(char *s, char *es, char *t, char *et)
{
	int	ret;

	return (ret);
}

t_cmd	*parsepipe(char **s, char *es)
{
	t_cmd	*cmd;

	
	return (cmd);
}

t_cmd	*parseline(char **s, char *es)
{
	t_cmd	*cmd;

	cmd = parsepipe(*s, es);
	return (cmd);
}

t_cmd	*parser(char *line, char **envp)
{
	t_cmd	*cmd;
	char	*es;

	es = line + ft_strlen(line);
	cmd = parseline(line, es);
	return (cmd);
}
