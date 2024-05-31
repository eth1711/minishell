/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlim <etlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:33:15 by etlim             #+#    #+#             */
/*   Updated: 2024/05/30 17:05:40 by etlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check the string that is being inputed, for example
//it takes in export USER=blahblahblah
//this function should check the before the equal sign (USER=)
//and check whether it is an alphabet or a permissible character(underscore only)
//it returns a char pointer back to ft_export
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
                free(args[i]);
                args[i] = ft_strdup(" ");
            }
        }
    }
    return(args);
    
}

//the export function takes a string from the terminal, checks it
// and throws it into the env if conditions/checks are ok
void	ft_export(char **args_array, t_env *envp)
{
    if(!check_env(*args_array, envp))
        put_env(*args_array, envp);
    else
        return ;
}