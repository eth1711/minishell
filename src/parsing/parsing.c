/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:01:10 by amaligno          #+#    #+#             */
/*   Updated: 2024/01/30 20:40:23 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char *line, char **envp)
{
	char	**tokens;
	char	*tmp;
	int		id;

	(void)line;
	tokens = ft_split(line, ' ');
	tmp = tokens[0];
	tokens[0] = ft_strjoin("/usr/bin/", tokens[0]);
	id = fork();
	if (!id)
	{
		if (execve(tokens[0], tokens, NULL) == -1)
		{
			printf("%s: command not found \n", tmp);
			exit(0);
		}
	}
	else
		wait(&id);
	(void)envp;
	free (tmp);
}
