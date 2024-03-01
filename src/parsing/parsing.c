/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:01:10 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/01 21:54:32 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parseredir(char **s, char *es, t_cmd *cmd)
{
	int			tok;
	t_strptrs	toks;

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

t_cmd	*parseexec(char **s, char *es)
{
	t_types		ptrs;
	t_strptrs	toks;
	int			i;
	int			tok;

	i = 0;
	ptrs.exec = (t_execcmd *)execmd();
	ptrs.cmd = parseredir(s, es, (t_cmd *)ptrs.exec);
	while (!checktoken(s, es, SYMBOLS))
	{
		tok = gettoken(s, es, &toks.s, &toks.es);
		if (tok != 'a')
			break ;
		expansion(toks.s, toks.es, ptrs.exec);
		ptrs.cmd = parseredir(s, es, ptrs.cmd);
	}
	return (ptrs.cmd);
}

t_cmd	*parsepipe(char **s, char *es)
{
	t_cmd	*cmd;

	// printf("parsepipe: enter\n");
	cmd = parseexec(s, es);
	if (checktoken(s, es, "|"))
	{
		// printf("parsepipe: inside if: **s: %c\n", **s);
		// printf("parsepipe: checktoken found pipe\n");
		gettoken(s, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(s, es));
	}
	return (cmd);
}

t_cmd	*parser(char *line)
{
	t_cmd	*cmd;
	char	*es;

	es = line + ft_strlen(line);
	cmd = parsepipe(&line, es);
	return (cmd);
}
