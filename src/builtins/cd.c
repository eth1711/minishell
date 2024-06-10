/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlim <etlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:11:06 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/10 20:22:24 by etlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	upd_old_pwd(char *args, t_env *envp)
{
	
}

void	upd_pwd(char *args, t_env *envp)
{
	while (*args)
	{
		while (envp->next && ft_strncmp(envp->key, "PWD=", 4))
        	envp = envp->next;
		if(!ft_strncmp(env->key, "PWD=", 4))	
		
	}
}


void	ft_cd(char	*args_array)
{
	if (!args_array)
		return (NULL);
	chdir(args_array);
	
}
