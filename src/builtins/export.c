/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlim <etlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:33:15 by etlim             #+#    #+#             */
/*   Updated: 2024/05/29 18:56:23 by etlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *check_env(char *args, t_env *envp)
{
    int i;
    
    i = 0;
    if (!envp)
        return (NULL);
    while (args[i])
    {
        if (ft_isalpha(args[i]))
        {
            if (!ft_strchr(args[i], '='))
            {
                free(agrs[i]);
                args[i] = ft_strdup(" ");
            }   
        }
    }
    return(args);
    
}
void	ft_export(char **args_array, t_env *envp)
{
    if(!check_env(*args_array, envp))
        put_env(*args_array, envp);
    else
        return ;
}