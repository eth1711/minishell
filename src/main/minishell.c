/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlim <etlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:50 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/07 20:33:38 by etlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	line = readline("minishell$ ");

    int count = 0;
    while (envp)
    {
        ft_strncmp(*envp, "HOME=", );
        envp++;
    }
	while (line)
	{
		add_history(line);
		if (line && *line)
			print_tree(parser(line));
		line = readline("minishell$ ");
	}
	exit(0);
	(void)envp;
	return (0);
}
