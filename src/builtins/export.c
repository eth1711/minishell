/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:33:15 by etlim             #+#    #+#             */
/*   Updated: 2024/06/19 17:57:22 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check the string that is being inputed, for example
//it takes in export USER=blahblahblah
//this function should check the before the equal sign (USER=)
//and check whether it is an alphabet or a permissible character(underscore only)
//it returns a char pointer back to ft_export
char	*check_env(char *args)
{
	int i;

	i = -1;
	printf("%s\n", args);
	while (args && args[++i])
	{
		printf("%c\n", args[i]);
		if (ft_isalpha(args[i]) || !ft_strchr(args, '_'))
		{
			if (!ft_strchr(args, '='))
			{
				printf("came into if statement\n");
				free(args);
				args = ft_strdup(" ");
				return (args);
			}   
		}
	}
	return (args);
}

//the export function takes a string from the terminal, checks it
// and throws it into the env if conditions/checks are ok
void	ft_export(char **args_array, t_env *envp)
{
	args_array++;
	printf("coming in to ft_export %s\n", *args_array);
	if(*args_array == NULL)
	{
		while (envp)
		{
			printf("declare -x %s=%s\n", envp->key, envp->value);
			envp = envp->next;
		}
	}
	while(check_env(*args_array))
	{
		if ((*args_array)[0] == ' ')
			return ;
		put_env(*args_array, &envp);
		args_array++;
		printf("in while loop %s\n", *args_array);
	}
	return ;
}
