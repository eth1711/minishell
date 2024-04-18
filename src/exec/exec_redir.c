/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:47:27 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/18 19:28:34 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(char *delimiter, t_env *envp)
{
	int 		fds[2];
	char		*line;
	t_strptrs	toks;

	pipe(fds);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	close(fds[1]);
	line = readline("heredoc>");
	while (line && ft_strcmp(line, delimiter))
	{
		toks.s = line;
		toks.es = line + ft_strlen(line);
		line = expansion(toks, NULL, envp);
		ft_putstr_fd(line, fds[0]);
		free(toks.s);
		line = readline("heredoc>");
	}
}

void	exec_redir(t_redircmd *redir, t_env *envp)
{
	int	fd;

	if (redir->mode == LL)
		heredoc(redir->filename, envp);
	else
	{
		fd = open(redir->filename, redir->mode);
		dup2(fd, redir->fd);
		close(fd);
	}
	exec_execcmd(redir->cmd, envp);
}
