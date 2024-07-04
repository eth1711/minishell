/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:33:15 by etlim             #+#    #+#             */
/*   Updated: 2024/07/04 14:29:52 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

//check the string that is being inputed, for example
//it takes in export USER=blahblahblah
//this function should check the before the equal sign (USER=) and
//check whether it is an alphabet or a permissible character(underscore only)
//it returns a char pointer back to ft_export
int	check_env(char *args)
{
	int	i;

	i = 0;
	if (!ft_isalpha(args[i]) && args[i] != '_')
		return (printf("minish: export: not a valid identifier\n"), 0);
	if (!ft_strchr(args, '='))
		return (0);
	while (*args && args[++i])
	{
		if (args[i] == '=')
			return (1);
		if (!ft_isalnum(args[i]) && args[i] != '_'
			&& !ft_strchr(WHITESPACE, args[i]))
			return (printf("minish: export: not a valid identifier\n"), 0);
	}
	return (1);
}

//the export function takes a string from the terminal, checks it
// and throws it into the env if conditions/checks are ok
void	ft_export(char **args_array, t_env *envp)
{
	char	**pair;

	args_array++;
	if (*args_array == NULL)
	{
		while (envp)
		{
			printf("declare -x %s=%s\n", envp->key, envp->value);
			envp = envp->next;
		}
	}
	while (args_array && *args_array)
	{
		if (check_env(*args_array))
		{
			pair = key_value_splitter(*args_array);
			put_env(pair[0], pair[1], &envp);
			free(pair[0]);
			free(pair);
		}
		else
			g_error = 1;
		args_array++;
	}
	g_error = 0;
}
