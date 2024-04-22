/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:29:07 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/22 09:38:40 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **args, t_env *envp)
{
	(void)envp;
	if (!ft_strcmp(args[0], "echo"))
		return (/*ft_echo(args),*/ printf("ft_echo\n"), 1);
	if (!ft_strcmp(args[0], "cd"))
		return (/*ft_cd(args),*/printf("ft_cd\n"), 1);
	if (!ft_strcmp(args[0], "export"))
		return (/*ft_export(args, envp),*/ printf("ft_export\n"), 1);
	if (!ft_strcmp(args[0], "pwd"))
		return (/*ft_pwd(args, envp),*/ printf("ft_echo\n"), 1);
	if (!ft_strcmp(args[0], "unset"))
		return (/*ft_unset(args, envp),*/ printf("ft_echo\n"), 1);
	if (!ft_strcmp(args[0], "exit"))
		return (/*ft_exit(args, envp),*/ printf("ft_echo\n"), 1);
	return (0);
}

// int	reset_signals()
// {
// 	signal(CTRL_C, SIG_DFL);
// 	signal(CTRL_SLSH, SIG_DFL);
// }