/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execcmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlim <etlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:21:01 by amaligno          #+#    #+#             */
/*   Updated: 2024/07/09 16:30:50 by etlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

int	is_builtin(char **args, t_env *envp, int *fds_pipe)
{
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args, envp), 1);
	if (!ft_strcmp(args[0], "export"))
	{
		dup2(fds_pipe[1], STDOUT_FILENO);
		ft_export(args, envp);
		close(STDOUT_FILENO);
		dup2(STDERR_FILENO, STDOUT_FILENO);
		return (1);
	}
	if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args, envp), 1);
	if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args), 1);
	return (0);
}

int	is_fork_builtin(char **args)
{
	if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd(), 1);
	if (!ft_strcmp(args[0], "echo"))
	{
		g_error = 0;
		return (ft_echo(args), 1);
	}
	return (0);
}

//Returns the path of the given command, if not found it returns NULL
// char	*find_command(char *cmd, t_env *envp)

char	*find_command(char *cmd, t_env *envp)
{
	char	**ptr;
	char	**paths;
	char	*ret;

	if (!*cmd || !access(cmd, F_OK | X_OK))
		return (cmd);
	cmd = ft_strjoin("/", cmd);
	paths = ft_split(get_env("PATH", envp), ':');
	if (!paths)
		return (free(cmd), NULL);
	ptr = paths;
	while (*ptr)
	{
		ret = ft_strjoin(*ptr, cmd);
		if (!access(ret, F_OK | X_OK))
			return (free_2d((void **)paths), free(paths), free(cmd), ret);
		free(ret);
		ptr++;
	}
	return (free_2d((void **)paths), free(paths), free(cmd), NULL);
}

void	exec_execcmd(t_execcmd *exec, t_env *envp, int *fds_pipe)
{
	char	**envp_array;
	char	*path;
	pid_t	pid;

	if (!exec->args_array[0] || !exec->args_array[0][0] ||
		is_builtin(exec->args_array, envp, fds_pipe))
		return ;
	pid = fork();
	if (!pid)
	{
		dup2(fds_pipe[0], STDIN_FILENO);
		dup2(fds_pipe[1], STDOUT_FILENO);
		close(fds_pipe[2]);
		if (is_fork_builtin(exec->args_array))
			exit(0);
		envp_array = env_to_array(envp);
		path = find_command(exec->args_array[0], envp);
		execve(path, exec->args_array, envp_array);
		ft_putstr_fd("minish: ", STDERR_FILENO);
		ft_putstr_fd(exec->args_array[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
}
