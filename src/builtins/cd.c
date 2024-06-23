/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:11:06 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/23 23:14:44 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_dir(t_env *envp)
{
	char	*home;

	home = NULL;
	while (envp->next && ft_strcmp("HOME", envp->key))
		envp = envp->next;
	if (!ft_strcmp("HOME", envp->key))
		home = envp->value;
	return (home);
}

int	count_args(char **args_array)
{
	int	count;

	count = 0;
	while (args_array[count])
		count++;
	if (count > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	return (0);
}

void	ft_cd(char **args_array, t_env *envp)
{
	char	*cwd;

	if (count_args(args_array))
		return ;
	cwd = getcwd(NULL, 0);
	if (!args_array[1])
	{
		chdir(get_home_dir(envp));
		return ;
	}
	args_array++;
	if (chdir(*args_array) == 0)
	{
		put_env(ft_strdup("OLDPWD"), cwd, &envp);
		cwd = getcwd(NULL, 0);
		put_env(ft_strdup("PWD"), cwd, &envp);
		return ;
	}
	free(cwd);
	printf("minish: cd: %s: %s\n", *args_array, strerror(errno));
}
