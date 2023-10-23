/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:50 by amaligno          #+#    #+#             */
/*   Updated: 2023/10/23 20:14:56 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string.h"

int	main(int argc, char *argv[])
{
	char	*input;

	printf("hello\n");
	(void)argc;
	(void)argv;
	input = readline("minishell$ ");
	while (1)
	{
		input = readline("minishell$ ");
		if (strcmp(input, "hello") == 0)
			printf("hi :)\n");
	}
	return (0);
}
