/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:29:07 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/02 17:23:43 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **args, t_env *envp)
{
	if (ft_strcmp(args[0], "echo"))
		return (ft_echo(args), 1);
	if (ft_strcmp(args[0], "cd"))
		return (ft_cd(args), 1);
	if (ft_strcmp(args[0], "export"))
		return (ft_export(args, envp), 1);
	if (ft_strcmp(args[0], "pwd"))
		return (ft_pwd(args, envp), 1);
	if (ft_strcmp(args[0], "unset"))
		return (ft_unset(args, envp), 1);
	if (ft_strcmp(args[0], "exit"))
		return (ft_exit(args, envp), 1);
	return (0);
}
