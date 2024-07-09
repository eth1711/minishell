/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:47:27 by amaligno          #+#    #+#             */
/*   Updated: 2024/07/09 17:15:29 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

static void	flag_setter(int *flag_add)
{
	static int	*flag;

	if (!flag_add)
		*flag = 1;
	else
	{
		flag = flag_add;
		*flag = 0;
	}
}

static void	sigint_handler(int sigint)
{
	(void)sigint;
	flag_setter(NULL);
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
		line = expansion(toks, NULL, envp, 1);
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

int	heredoc(char *delimiter, t_env *envp, int *fds_pipe)
{
	int		fds[2];
	int		flag;

	flag_setter(&flag);
	pipe(fds);
	signal(CTRL_C, sigint_handler);
	heredoc_helper(delimiter, fds, envp);
	close(fds[1]);
	if (!flag)
	{
		fds_pipe[0] = fds[0];
		return (1);
	}
	signal(CTRL_C, ignore_sig);
	return (close(fds[0]), 0);
}

void	exec_redir(t_redircmd *redir, t_env *envp, int *fds_pipe)
{
	int	fd;

	if (redir->mode == LL)
	{
		if (!heredoc(redir->filename, envp, fds_pipe))
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
	exec(redir->cmd, envp, fds_pipe);
}
