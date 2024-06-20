/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlim <etlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:11:06 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/20 17:30:25 by etlim            ###   ########.fr       */
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

void	ft_cd(char	**args_array, t_env *envp)
{
	if (!args_array[1])
	{
		chdir(get_home_dir(envp));
		return ;
	}
	args_array++;
	if ()
	{
		if (chdir(args_array) == 0)
		{
			upd_env(*args_array, "OLD_PWD", envp);
			upd_env(*args_array, "PWD", envp);
		}
	}
}
