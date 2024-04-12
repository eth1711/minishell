/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execcmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:21:01 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/12 14:26:36 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Returns the path of the given command, if not found NULL
char	*find_command(char *cmd, t_env *envp)
{
	char		*path;
	struct stat	stats;

	if (stat(cmd, &stats) && !(stats.st_mode & S_IFDIR))
		return (cmd);
	path = get_env("PATH", envp);
	while ()
	return (NULL);
}

void	exec_execcmd(t_execcmd *exec, t_env *envp)
{
	int		pid;
	int		ret;
	char	**envp_array;

	if (is_builtin(exec->args_array, envp))
		return ;
	pid = fork();
	if (!pid)
	{
		execve(exec->args_array[0], exec->args_array, env_to_array(envp));
		ft_putstr_fd("minish: command not found: ", STDERR_FILENO);
		ft_putstr_fd(exec->args_array[0], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		exit(-1);
	}
}
