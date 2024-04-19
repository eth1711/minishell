/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execcmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:21:01 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/19 17:15:50 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Returns the path of the given command, if not found NULL
// char	*find_command(char *cmd, t_env *envp)

char	*find_command(char *cmd, t_env *envp)
{
	char		**paths;
	char		*ret;

	if (!access(cmd, F_OK | X_OK))
		return (cmd);
	cmd = ft_strjoin("/", cmd);
	paths = ft_split(get_env("PATH", envp), ':');
	while (*paths)
	{
		ret = ft_strjoin(*paths, cmd);
		if (!access(ret, F_OK | X_OK))
			return (free_2d(paths), free(cmd), ret);
		free(ret);
		paths++;
	}
	return (free_2d(paths), free(cmd), NULL);
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
		printf("l57: exec_execcmd: execve: %i\n", execve(path, exec->args_array, env_to_array(envp)));
		ft_putstr_fd("minish: command not found: ", STDERR_FILENO);
		ft_putstr_fd(exec->args_array[0], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		exit(127);
	}
}
