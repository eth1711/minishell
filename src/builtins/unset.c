/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlim <etlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:33:24 by etlim             #+#    #+#             */
/*   Updated: 2024/06/19 14:55:43 by etlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **args_array, t_env *envp)
{
    if (!(**args_array))
    {
        ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
    }
    while (**args_array && *args_array)
    {
        while (envp->next && ft_strcmp(envp->key, *args_array))
            envp = envp->next;
        if (!ft_strcmp(envp->key, *args_array))
        {
            envp->next->prev = envp->prev;
            envp->prev->next = envp->next;
            free(envp);
        }
        (*args_array)++;
        // printf("iter num\n");
    }
}