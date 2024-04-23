/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:47:27 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/23 17:47:16 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int sig)
{
	(void)sig;
}

int	heredoc(char *delimiter, t_env *envp, int *fds)
{
	char		*line;
	t_strptrs	toks;

	signal(CTRL_C, SIG_DFL);
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
	exit(0);
}

int	fork_heredoc(char *delimiter, t_env *envp)
{
	int	fds[2];
	int	pid;
	int	status;

	pipe(fds);
	pid = fork();
	if (!pid)
		heredoc(delimiter, envp, fds);
	signal(CTRL_C, handler);
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	waitpid(pid, &status, 0);
	init_signals();
	return (status);
}

int	exec_redir(t_redircmd *redir, t_env *envp, pid_t *pids)
{
	int	fd;

	if (redir->mode == LL)
	{
		if (fork_heredoc(redir->filename, envp))
			return (ft_putchar_fd('\n', STDERR_FILENO), 0);
	}
	else
	{
		fd = open(redir->filename, redir->mode, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("minish: ", STDERR_FILENO);
			ft_putstr_fd(redir->filename, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			return (0);
		}
		dup2(fd, redir->fd);
		close(fd);
	}
	return (exec_execcmd((t_execcmd *)redir->cmd, envp, pids));
}
