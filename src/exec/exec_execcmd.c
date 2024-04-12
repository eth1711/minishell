/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execcmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:21:01 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/12 22:14:43 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Returns the path of the given command, if not found NULL
char	*find_command(char *cmd, t_env *envp)
{
	char		*env_path;
	char		*tmp;
	int			count;
	struct stat	stats;

	if (stat(cmd, &stats) && !(stats.st_mode & S_IFDIR)
		&& (stats.st_mode & S_IXUSR))
		return (cmd);
	env_path = get_env("PATH", envp);
	while (*env_path)
	{
		count = 0;
		while (env_path[count] && env_path[count] != ':')
			count++;
		tmp = ft_safejoin(ft_substr(env_path, 0, count), ft_strdup(cmd));
		if (stat(tmp, &stats) && !(stats.st_mode & S_IFDIR)
			&& (stats.st_mode & S_IXUSR))
			return (tmp);
		free(tmp);
		if (env_path[count] == ':')
			count++;
		env_path += count;
	}
	return (NULL);
}

void	exec_execcmd(t_execcmd *exec, t_env *envp)
{
	int		pid;
	int		ret;
	char	**envp_array;
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
		exit(-1);
	}
}
