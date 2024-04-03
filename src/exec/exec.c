/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:31:04 by etlim             #+#    #+#             */
/*   Updated: 2024/04/03 17:59:06 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_redir(t_redircmd *redir, t_env *envp)
{
	
}

char	*find_command(char *cmd, t_env *envp)
{
	char		*path;	
	struct stat	stats;
	
	if (ft_strchr("./", cmd[0]) || ft_strchr("/", cmd[1]))
		return (cmd);
	path = get_env("PATH", envp);
	
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

void	exec_pipe(t_pipecmd *pipe, t_env *envp)
{
	
}

void	exec(t_cmd *head, t_env *envp)
{
	static int	children;

	if (head->type == PIPE)
	{
		exec_pipe((t_pipecmd *)head, envp);
		children += 2;
	}
	else if (head->type == EXEC)
		exec_cmd((t_execcmd *)head, envp);
	else if (head->type == REDIR)	
		exec_redir((t_redircmd *)head, envp);
	while (children)
	{
		wait(0);
		children--;
	}
}