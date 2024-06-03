/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:24:37 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/03 15:47:40 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

// void	exec_pipe(t_pipecmd *pipecmd, t_env *envp)
// {
// 	int		fds[2];
// 	pid_t	pids[2];

// 	pipe(fds);
// 	pids[0] = fork();
// 	if (!pids[0])
// 	{
// 		dup2(fds[1], STDOUT_FILENO);
// 		close(fds[0]);
// 		close(fds[1]);
// 		exec(pipecmd->left, envp, 1);
// 	}
// 	pids[1] = fork();
// 	if (!pids[1])
// 	{
// 		dup2(fds[0], STDIN_FILENO);
// 		close(fds[0]);
// 		close(fds[1]);
// 		exec(pipecmd->right, envp, 0);
// 	}
// 	close(fds[0]);
// 	close(fds[1]);
// 	waitpid(pids[0], &g_error, 0);
// 	waitpid(pids[1], &g_error, 0);
// 	exit(0);
// }

void	exec_pipe(t_pipecmd *pipecmd, t_env *envp, int *fds_pipe)
{
	int		fds[2];
	int		fds_left[3];
	int		fds_right[3];

	pipe(fds);
	fds_left[0] = fds_pipe[0];
	fds_left[1] = fds[1];
	fds_left[2] = fds[0];
	exec(pipecmd->left, envp, 0, fds_left);
	close(fds[1]);
	fds_right[0] = fds[0];
	fds_right[1] = STDOUT_FILENO;
	fds_right[2] = -1;
	exec(pipecmd->right, envp, 0, fds_right);
	close(fds[0]);
}
