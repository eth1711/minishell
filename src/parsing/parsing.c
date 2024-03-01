/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:01:10 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/01 20:25:57 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parseredir(char **s, char *es, t_cmd *cmd)
{
	int			tok;
	t_token		toks;

	printf("parsredir: enter\n");
	while (checktoken(s, es, "<>"))
	{
		printf("parsredir: enter while\n");
		tok = gettoken(s, es, 0, 0);
		gettoken(s, es, &toks.t, &toks.et);
		if (tok == '>')
			cmd = redircmd(cmd, 1, O_WRONLY | O_CREAT | O_TRUNC, toks);
		else if (tok == '<')
			cmd = redircmd(cmd, 0, O_RDONLY, toks);
		else if (tok == RR)
			cmd = redircmd(cmd, 1, O_RDONLY | O_CREAT, toks);
		else if (tok == LL)
			cmd = redircmd(cmd, 0, O_RDONLY, toks);
	}
	printf("parsredir: return\n");
	return (cmd);
}

//i need 5 vars in parseexec two of which are struct pointers so i 
//use the types struct to not need to declare each ptr

t_cmd	*parseexec(char **s, char *es)
{
	t_types		ptrs;
	t_token		toks;
	int			i;

	i = 0;
	ptrs.exec = (t_execcmd *)execmd(argcount(*s, es));
	ptrs.cmd = parseredir(s, es, (t_cmd *)ptrs.exec);
	while (!checktoken(s, es, SYMBOLS))
	{
		if (gettoken(s, es, &toks.t, &toks.et) != 'a')
			break ;
		ptrs.exec->argv[i] = toks.t;
		ptrs.exec->eargv[i++] = toks.et;
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
		printf("parsepipe: inside if: **s: %c\n", **s);
		printf("parsepipe: checktoken found pipe\n");
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
