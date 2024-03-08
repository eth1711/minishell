/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:01:10 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/08 16:55:11 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parseredir(char **s, char *es, t_cmd *cmd, t_env *env)
{
	int			tok;
	t_strptrs	toks;

	(void)env;
	printf("parsredir: enter\n");
	while (checktoken(s, es, "<>"))
	{
		printf("parsredir: enter while\n");
		tok = gettoken(s, es, 0, 0);
		gettoken(s, es, &toks.s, &toks.es);
		if (tok == '>')
			cmd = redircmd(cmd, 1, O_WRONLY | O_CREAT | O_TRUNC, toks);
		else if (tok == '<')
			cmd = redircmd(cmd, 0, O_RDONLY, toks);
		else if (tok == RR)
			cmd = redircmd(cmd, 1, O_RDONLY | O_CREAT, toks);
		else if (tok == LL)
			cmd = redircmd(cmd, 0, LL, toks);
	}
	// printf("parsredir: return\n");
	return (cmd);
}

//i need 5 vars in parseexec two of which are struct pointers so i 
//use the types struct to not need to declare each ptr

t_cmd	*parseexec(char **s, char *es, t_env *env)
{
	t_types		ptrs;
	t_strptrs	toks;
	int			tok;

	ptrs.exec = (t_execcmd *)execmd();
	ptrs.cmd = parseredir(s, es, (t_cmd *)ptrs.exec, env);
	while (!checktoken(s, es, SYMBOLS))
	{
		tok = gettoken(s, es, &toks.s, &toks.es);
		if (tok != 'a')
			break ;
		expansion(toks, ptrs.exec, env);
		ptrs.cmd = parseredir(s, es, ptrs.cmd, env);
	}
	return (ptrs.cmd);
}

t_cmd	*parsepipe(char **s, char *es, t_env *env)
{
	t_cmd	*cmd;

	// printf("parsepipe: enter\n");
	cmd = parseexec(s, es, env);
	if (checktoken(s, es, "|"))
	{
		// printf("parsepipe: inside if: **s: %c\n", **s);
		// printf("parsepipe: checktoken found pipe\n");
		gettoken(s, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(s, es, env));
	}
	return (cmd);
}

t_cmd	*parser(char *line, t_env *env)
{
	t_cmd	*cmd;
	char	*es;

	es = line + ft_strlen(line);
	if (!check_quotes(line, es))
		return (NULL);
	cmd = parsepipe(&line, es, env);
	return (cmd);
}
