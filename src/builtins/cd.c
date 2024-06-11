/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlim <etlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:11:06 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/11 18:49:23 by etlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	upd_env(char *args, char *key, t_env *envp)
{
	int	pwd;

	pwd = NULL;
	while (envp->next && !ft_strcmp(envp->key, key))
    	envp = envp->next;
	if (ft_strcmp(env->key, "OLD_PWD") == 0)
		pwd = ((ft_strlen(args) - ft_strlen("OLD_PWD=")) - 2)
		free(envp->value);
		while(args[++pwd])
			envp->prevvalue = args[pwd];
	else if (ft_strcmp(env->key, "PWD") == 0)
		pwd = ((ft_strlen(args) - ft_strlen("PWD=")) - 2)
		free(envp->value);
		while(args[++pwd])
			envp->value = args[pwd];
}


void	ft_cd(char	*args_array, t_env *envp)
{
	if (!args_array)
		return (NULL);
	chdir(args_array);
	upd_env(args_array, "PWD", envp);
	upd_env(args_array, "OLD_PWD", envp);
	
}
