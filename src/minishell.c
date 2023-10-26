/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:20:50 by amaligno          #+#    #+#             */
/*   Updated: 2023/10/26 17:54:23 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string.h"

int	main(int argc, char *argv[])
{
	char	*input;

	(void)argc;
	(void)argv;
	input = readline("minishell$ ");
	while (1)
	{
		if (strcmp(input, "hello") == 0)
			printf("hi :)\n");
		input = readline("minishell$ ");
	}
	return (0);
}
