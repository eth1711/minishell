/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlim <etlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:11:06 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/20 18:44:31 by etlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	upd_env(char *args, char *key, t_env *envp)
{
	int	pwd;

	while (envp->next && !ft_strcmp(envp->key, key))
    	envp = envp->next;
	// if (!envp->next)
	if (ft_strcmp(envp->key, "OLD_PWD") == 0)
	{
		pwd = ((ft_strlen(args) - ft_strlen("OLD_PWD=")) - 2);
		free(envp->prev->value);
		envp->prev->value = envp->value;
	}
	else if (ft_strcmp(envp->key, "PWD") == 0)
	{
		pwd = ((ft_strlen(args) - ft_strlen("PWD=")) - 2);
		free(envp->value);
		while(args[++pwd])
			envp->value = &args[pwd];
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
	while (*args_array[count])
		count++;
	if (count > 1)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	return (count > 1);
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
		*args_array = ft_safejoin(ft_strdup("./"), *args_array);
	if (chdir(*args_array) == 0)
	{
		upd_env(cwd, "OLD_PWD", envp);
		upd_env(*args_array, "PWD", envp);
		return ;
	}
	else
		printf("wip%s\n", strerror(errno));
}
