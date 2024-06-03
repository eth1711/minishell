/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:47:27 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/03 15:56:26 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

static void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	close(STDIN_FILENO);
}

void	heredoc(char *delimiter, t_env *envp, int *fds_pipe)
{
	int			fds[2];
	char		*line;
	t_strptrs	toks;
	pipe(fds);
	// dup2(FD_STDIN, STDOUT_FILENO);
	// dup2(FD_STDOUT, STDOUT_FILENO);
	signal(CTRL_C, sigint_handler);
	line = readline("heredoc> ");
	while (line && *line)
	{
		toks.s = line;
		toks.es = line + ft_strlen(line);
		line = expansion(toks, NULL, envp);
		free(toks.s);
		if (!ft_strcmp(line, delimiter))
			break ;
		ft_putstr_fd(line, fds[1]);
		ft_putchar_fd('\n', fds[1]);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	close(fds[1]);
	fds_pipe[0] = fds[0];
}

// void	heredoc(char *delimiter, t_env *envp, int fd)
// {
// 	char		*line;
// 	t_strptrs	toks;

// 	signal(CTRL_C, SIG_DFL);
// 	line = readline("heredoc> ");
// 	ft_putstr_fd("l24: heredoc\n", STDERR_FILENO);
// 	while (line && *line && ft_strcmp(line, delimiter))
// 	{
// 		ft_putstr_fd("l27: heredoc\n", STDERR_FILENO);
// 		toks.s = line;
// 		toks.es = line + ft_strlen(line);
// 		line = expansion(toks, NULL, envp);
// 		free(toks.s);
// 		ft_putstr_fd(line, fd);
// 		ft_putchar_fd('\n', fd);
// 		free(line);
// 		line = readline("heredoc> ");
// 	}
// 	ft_putstr_fd("l37: heredoc\n", STDERR_FILENO);
// 	// clear_history();
// 	// exit(0);
// }


// int	fork_heredoc(char *delimiter, t_env *envp)
// {
// 	int	fds[2];
// 	// int	pid;
	
// 	pipe(fds);
// 	// pid = fork();
// 	// if (!pid)
// 	heredoc(delimiter, envp, fds[1]);
// 	dup2(fds[0], STDIN_FILENO);
// 	close(fds[0]);
// 	// waitpid(pid, &g_error, 0);
// 	ft_putstr_fd("l54: fork_heredoc\n", STDERR_FILENO);
// 	return (g_error);
// }

void	exec_redir(t_redircmd *redir, t_env *envp, int forked, int *fds_pipe)
{
	int	fd;

	if (redir->mode == LL)
		heredoc(redir->filename, envp, fds_pipe);
	else
	{
		fd = open(redir->filename, redir->mode, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("minish: ", STDERR_FILENO);
			ft_putstr_fd(redir->filename, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			exit(1);
		}
		dup2(fd, fds_pipe[redir->fd]);
		close(fd);
	}
	exec(redir->cmd, envp, forked, fds_pipe);
}
