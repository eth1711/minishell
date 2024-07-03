/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:01:10 by amaligno          #+#    #+#             */
/*   Updated: 2024/07/03 15:43:06 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parseredir(char **s, char *es, t_cmd *cmd, t_env *env)
{
	int			tok;
	t_strptrs	toks;

	while (checktoken(s, es, "<>"))
	{
		tok = gettoken(s, es, 0, 0);
		gettoken(s, es, &toks.s, &toks.es);
		if (!*toks.s || ft_strchr("<>|", *toks.s))
			return (error(cmd, ERR_SYTX_RDIR, 258));
		if (tok == LL)
			cmd = redircmd(cmd, 0, LL, ft_substr(toks.s, 0, toks.es - toks.s));
		else
		{
			toks.s = expansion(toks, NULL, env, 0);
			if (tok == '>')
				cmd = redircmd(cmd, 1, O_WRONLY | O_CREAT | O_TRUNC, toks.s);
			else if (tok == '<')
				cmd = redircmd(cmd, 0, O_RDONLY, toks.s);
			else if (tok == RR)
				cmd = redircmd(cmd, 1, O_RDWR | O_CREAT | O_APPEND, toks.s);
		}
	}
	return (cmd);
}

//i need 5 vars in parseexec two of which are struct pointers so i 
//use the types struct to not need to declare each ptr

t_cmd	*parseexec(char **s, char *es, t_env *env)
{
	t_types		ptrs;
	t_strptrs	toks;
	int			tok;

	ptrs.exec = (t_execcmd *)execcmd();
	ptrs.cmd = parseredir(s, es, (t_cmd *)ptrs.exec, env);
	while (**s && !checktoken(s, es, SYMBOLS) && ptrs.cmd->type != ERROR)
	{
		tok = gettoken(s, es, &toks.s, &toks.es);
		if (tok != 'a')
			break ;
		expansion(toks, ptrs.exec, env, 0);
		ptrs.cmd = parseredir(s, es, ptrs.cmd, env);
	}
	list_to_array(ptrs.exec);
	return (ptrs.cmd);
}

t_cmd	*parsepipe(char **s, char *es, t_env *env)
{
	t_cmd	*cmd;
	t_cmd	*pipe;

	cmd = parseexec(s, es, env);
	if (checktoken(s, es, "|") && cmd->type != ERROR)
	{
		gettoken(s, es, 0, 0);
		if (!**s || checktoken(s, es, "|"))
			return (error(cmd, ERR_SYTX_PIPE, 258));
		pipe = parsepipe(s, es, env);
		if (pipe->type == ERROR)
			return (free_tree(pipe), error(cmd, NULL, 258));
		cmd = pipecmd(cmd, pipe);
	}
	return (cmd);
}

t_cmd	*parser(char *line, t_env *env)
{
	t_cmd	*cmd;
	char	*es;

	es = line + ft_strlen(line);
	if (!check_quotes(line, es))
	{
		ft_putstr_fd(ERR_QUOTES, STDERR_FILENO);
		return (NULL);
	}
	cmd = parsepipe(&line, es, env);
	return (cmd);
}
