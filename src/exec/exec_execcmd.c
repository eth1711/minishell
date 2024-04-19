/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execcmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:21:01 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/19 16:06:42 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Returns the path of the given command, if not found NULL
// char	*find_command(char *cmd, t_env *envp)

char	*find_command(char *cmd, t_env *envp)
{
	char		**paths;
	char		*ret;

	if (access(cmd, F_OK | X_OK))
		return (cmd);
	paths = ft_split(get_env("PATH", envp), ':');
	while (*paths)
	{
		ret = ft_strjoin(cmd, *paths);
		if (access(cmd, F_OK | X_OK))
			return (free_2d(paths), free(paths), free(ret), cmd);
		free(ret);
		paths++;
	}
	return (free_2d(paths), free(paths), NULL);
}

void	exec_execcmd(t_execcmd *exec, t_env *envp)
{
	int		pid;
	// int		ret;
	// char	**envp_array;
	char	*path;

	if (is_builtin(exec->args_array, envp))
		return ;
	pid = fork();
	if (!pid)
	{
		path = find_command(exec->args_array[0], envp);
		execve(path, exec->args_array, env_to_array(envp));
		ft_putstr_fd("minish: command not found: ", STDERR_FILENO);
		ft_putstr_fd(exec->args_array[0], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		exit(127);
	}
}
