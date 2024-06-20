/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlim <etlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:29:07 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/20 16:18:47 by etlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **args, t_env *envp)
{
	(void)envp;
	if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args), 1);
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args, envp), 1);
	if (!ft_strcmp(args[0], "export"))
		return (ft_export(args, envp), 1);
	if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd(), 1);
	if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args, envp), 1);
	if (!ft_strcmp(args[0], "exit"))
		exit(0);
	return (0);
}