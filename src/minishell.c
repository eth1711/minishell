/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:50 by amaligno          #+#    #+#             */
/*   Updated: 2023/10/27 15:44:31 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char *line, char **envp)
{
	char	**tokens;
	int		id;

	(void)envp;
	(void)line;
	tokens = ft_split(line, ' ');
	id = fork();
	if (!id)
	{
		if (execve(tokens[0], tokens, NULL) == -1)
		{
			printf("minish: command not found %s\n", tokens[0]);
			exit(0);
		}
	}
	else
		wait(&id);
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
