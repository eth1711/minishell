/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:47:27 by amaligno          #+#    #+#             */
/*   Updated: 2024/05/27 16:56:27 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *delimiter, t_env *envp)
{
	int			fds[2];
	char		*line;
	t_strptrs	toks;

	pipe(fds);
	signal(CTRL_C, SIG_DFL);
	line = readline("heredoc> ");
	while (line && *line && ft_strcmp(line, delimiter))
	{
		toks.s = line;
		toks.es = line + ft_strlen(line);
		line = expansion(toks, NULL, envp);
		free(toks.s);
		ft_putstr_fd(line, fds[1]);
		ft_putchar_fd('\n', fds[1]);
		free(line);
		line = readline("heredoc> ");
	}
	clear_history();
	exit(0);
}

void	exec_redir(t_redircmd *redir, t_env *envp)
{
	int	fd;

	if (redir->mode == LL)
	{
		if (heredoc(redir->filename, envp))
			return (ft_putchar_fd('\n', STDERR_FILENO));
	}
	else
	{
		fd = open(redir->filename, redir->mode, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("minish: ", STDERR_FILENO);
			ft_putstr_fd(redir->filename, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			return ;
		}
		dup2(fd, redir->fd);
		close(fd);
	}
	exec_execcmd((t_execcmd *)redir->cmd, envp);
}
