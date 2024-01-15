/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:50 by amaligno          #+#    #+#             */
/*   Updated: 2024/01/15 19:43:02 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char *line, char **envp)
{
	char	**tokens;
	char	*tmp;
	int		id;

	(void)envp;
	(void)line;
	tokens = ft_split(line, ' ');
	tmp = tokens[0];
	tokens[0] = ft_strjoin("/usr/bin/", tokens[0]);
	id = fork();
	if (!id)
	{
		if (execve(tokens[0], tokens, NULL) == -1)
		{
			printf("minish: command not found %s\n", tmp);
			exit(0);
		}
	}
	else
		wait(&id);
	free (tmp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	// (void)envp;
	(void)argc;
	(void)argv;
	// while (*envp)
	// 	printf("%s\n", *envp++);
	while (1)
	{
		line = readline("minishell$ ");
		// if (ft_strncmp(line, "hello", ft_strlen(line)) == 0)
			// printf("hi :) world\n");
		parser(line, envp);
	}
	return (0);
}
