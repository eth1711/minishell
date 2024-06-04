/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:47:27 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/04 16:25:29 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

static void	sigint_handler(int sigint)
{
	(void)sigint;
	g_error = 1;
	printf("\n");
	close(STDIN_FILENO);
}

void	heredoc_helper(char *delimiter, int *fds, t_env *envp)
{
	char		*line;
	t_strptrs	toks;

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
}

void	heredoc(char *delimiter, t_env *envp, int *fds_pipe)
{
	int			fds[2];

	pipe(fds);
	signal(CTRL_C, sigint_handler);
	heredoc_helper(delimiter, fds, envp);
	close(fds[1]);
	if (!g_error)
		fds_pipe[0] = fds[0];
	else
		close(fds[0]);
}

void	exec_redir(t_redircmd *redir, t_env *envp, int forked, int *fds_pipe)
{
	int	fd;

	if (redir->mode == LL)
	{
		heredoc(redir->filename, envp, fds_pipe);
		if (g_error)
			return ;
	}
	else
	{
		fd = open(redir->filename, redir->mode, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("minish: ", STDERR_FILENO);
			ft_putstr_fd(redir->filename, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			g_error = 1;
			return ;
		}
		dup2(fd, fds_pipe[redir->fd]);
		close(fd);
	}
	exec(redir->cmd, envp, forked, fds_pipe);
}
