/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlim <etlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:11:06 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/21 16:55:04 by etlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	upd_env(char *args, char *key, t_env *envp)
{	
	while (envp->next && ft_strcmp(envp->key, key))
    	envp = envp->next;
	if (!ft_strcmp(envp->key, key))
	{
		free(envp->value);
		envp->value = args;
	}
}

char *get_home_dir(t_env *envp)
{
	char *home;
	
	home = NULL;
	
	while (envp->next && ft_strcmp("HOME", envp->key))
		envp = envp->next;
	if (!ft_strcmp("HOME", envp->key))
		home = envp->value;
	return(home);
}

int	count_args(char **args_array)
{
	int count;

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

void	ft_cd(char	**args_array, t_env *envp)
{
	char *cwd;
	
	if(count_args(args_array))
		return ;
	cwd = getcwd(NULL, 0);
	if (!args_array[1])
	{
		chdir(get_home_dir(envp));
		return ;
	}
	args_array++;
	if (access(*args_array, F_OK) < 0)
	{
		*args_array = ft_safejoin(ft_strdup("./"), *args_array);
		// printf("hi2 %s\n", *args_array);
	}
	if (chdir(*args_array) == 0)
	{
		upd_env(cwd, "OLDPWD", envp);
		cwd = getcwd(NULL, 0);
		upd_env(cwd, "PWD", envp);
		return ;
	}
	else
		printf("wip %s\n", strerror(errno));
		return ;
		
}
