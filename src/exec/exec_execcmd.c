// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execcmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:21:01 by amaligno          #+#    #+#             */
/*   Updated: 2024/05/31 20:08:13 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_error;

//Returns the path of the given command, if not found NULL
// char	*find_command(char *cmd, t_env *envp)

char	*find_command(char *cmd, t_env *envp)
{
	char	**ptr;
	char	**paths;
	char	*ret;

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

void	exec_execcmd(t_execcmd *exec, t_env *envp, int forked, int *fds_pipe)
{
	char	**envp_array;
	char	*path;
	pid_t	pid;
	
	pid = 1;
	if (!exec->args_array[0] || is_builtin(exec->args_array, envp))
		return ;
	if (!forked)
		pid = fork();
	if (!pid || (pid && forked))
	{
		dup2(fds_pipe[0], STDIN_FILENO);
		dup2(fds_pipe[1], STDOUT_FILENO);
		close(fds_pipe[2]);
		envp_array = env_to_array(envp);
		path = find_command(exec->args_array[0], envp);
		execve(path, exec->args_array, envp_array);
		ft_putstr_fd("minish: ", STDERR_FILENO);
		ft_putstr_fd(exec->args_array[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free_2d(envp_array);
		free(path);
		exit(127);
	}
}
