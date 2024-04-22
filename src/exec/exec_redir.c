/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:47:27 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/22 16:54:53 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(char *delimiter, t_env *envp)
{
	int			fds[2];
	char		*line;
	t_strptrs	toks;

	pipe(fds);
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
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
}

int	exec_redir(t_redircmd *redir, t_env *envp, pid_t *pids)
{
	int	fd;

	if (redir->mode == LL)
	{
		heredoc(redir->filename, envp);
		init_signals();
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
