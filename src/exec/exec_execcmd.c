/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execcmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:21:01 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/22 11:07:50 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Returns the path of the given command, if not found NULL
// char	*find_command(char *cmd, t_env *envp)

char	*find_command(char *cmd, t_env *envp)
{
	char		**ptr;
	char		**paths;
	char		*ret;

	if (!access(cmd, F_OK | X_OK))
		return (cmd);
	cmd = ft_strjoin("/", cmd);
	paths = ft_split(get_env("PATH", envp), ':');
	ptr = paths;
	while (*ptr)
	{
		ret = ft_strjoin(*ptr, cmd);
		if (!access(ret, F_OK | X_OK))
			return (free_2d(paths), free(paths), free(cmd), ret);
		free(ret);
		ptr++;
	}
	return (free_2d(paths), free(paths), free(cmd), NULL);
}

int	exec_execcmd(t_execcmd *exec, t_env *envp, pid_t *pids)
{
	int		pid;
	// int		ret;
	char	**envp_array;
	char	*path;

	if (is_builtin(exec->args_array, envp))
		return (0);
	pid = fork();
	if (pids)
		pids[0] = pid;
	if (!pid)
	{
		signal(CTRL_C, SIG_DFL);
		signal(CTRL_SLSH, SIG_DFL);
		envp_array = env_to_array(envp);
		path = find_command(exec->args_array[0], envp);
		execve(path, exec->args_array, envp_array);
		ft_putstr_fd("minish: command not found: ", STDERR_FILENO);
		ft_putstr_fd(exec->args_array[0], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		// free_2d(envp_array);
		// free(path);
		exit(127);
	}
	return (1);
}
