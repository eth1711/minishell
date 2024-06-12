/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlim <etlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:29:25 by etlim             #+#    #+#             */
/*   Updated: 2024/06/12 14:34:34 by etlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    if (!pwd)
        ft_putstr_fd("Couldn't get current working directory\n", STDERR_FILENO);
    printf("%s\n", pwd);
    free(pwd);
}
