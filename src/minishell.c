/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:50 by amaligno          #+#    #+#             */
/*   Updated: 2024/01/16 20:26:08 by amaligno         ###   ########.fr       */
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
			printf("%s: command not found \n", tmp);
			exit(0);
		}
	}
	else
		wait(&id);
	free (tmp);
}

void	cd_cmnd(char *line)
{
	if (ft_strlen(line) > 3)
	{
		line[2] = '\0';
		if (chdir(line + 3) < 0)
			ft_putstr_fd("Cannot cd :( \n", 2);
	}
	else
		chdir("~");
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
		add_history(line);
		if (line && *line)
		{
			if (!ft_strncmp(line, "cd", 2))
				cd_cmnd(line);
			else
				parser(line, envp);
		}
	}
	return (0);
}
