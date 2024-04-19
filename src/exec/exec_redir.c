/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:47:27 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/19 21:28:13 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(char *delimiter, t_env *envp)
{
	int 		fds[2];
	char		*line;
	t_strptrs	toks;

	signal(CTRL_C, SIG_DFL);
	pipe(fds);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	line = readline("heredoc>");
	rl_on_new_line();
	ft_putstr_fd("l26: heredoc: line: [", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("]\n", 2);
	while ((*line && line) && ft_strcmp(line, delimiter))
	{
		rl_redisplay();
		toks.s = line;
		toks.es = line + ft_strlen(line);
		line = expansion(toks, NULL, envp);
		ft_putstr_fd(line, fds[0]);
		free(toks.s);
		line = readline("heredoc>");
		printf("l35: heredoc: line: [%s]\n", line);
	}
	close(fds[1]);
}

int		exec_redir(t_redircmd *redir, t_env *envp, pid_t *pids)
{
	int	fd;

	if (redir->mode == LL)
	{
		heredoc(redir->filename, envp);
		wait(0);
	}
	else
	{
		fd = open(redir->filename, redir->mode, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("minish: ", STDERR_FILENO);
			ft_putstr_fd(redir->filename, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
			return (0);
		}
		// printf("l46: exec_redir: fd: %i\n", fd);
		// printf("l48: exec_redir: redir->filename: %s\n", redir->filename);
		// printf("l49: exec_redir: redir->fd: %i\n", redir->fd);
		// printf("l50: exec_redir: redir->mode: %i\n", redir->mode);
		dup2(fd, redir->fd);
		close(fd);
	}
	return (exec_execcmd((t_execcmd *)redir->cmd, envp, pids));
}
