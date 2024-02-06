/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:39:02 by amaligno          #+#    #+#             */
/*   Updated: 2024/02/05 22:11:52 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function that skips whitespace, then returns 1 when pointer is not pointing
//to null, and points to one of the characters from the given string "find"
int	checktoken(char **s, char *es, char *find)
{
	while (*s < es && ft_strchr(WHITESPACE, **s))
		(*s)++;
	return (**s && ft_strchr(find, **s));
}

//helper function for gettoken
int	ret_value(char **s, char *es)
{
	int	ret;

	if (ft_strchr(SYMBOLS, **s))
	{
		ret = **s;
		(*s)++;
		if (**s == '<' && ret == '<')
			ret = LL;
		else if (**s == '>' && ret == '>')
			ret = RR;
		if (ret == RR || ret == LL)
			(*s)++;
	}
	else
	{
		ret = 'a';
		(*s)++;
		while (*s < es && !ft_strchr(WHITESPACE, **s)
			&& !ft_strchr(SYMBOLS, **s))
			(*s)++;
	}
	return (ret);
}

// Function that 'gets' the next token it can find, the return value indicates
// the token found:
// 'a' indicates an argument of a command, LL and RR indicate
// << and >> respectively and any other character returned indicates that symbol
// 0 if it is the end of the string
// (the turnary at the end checks if **s is null)
// s will be moved to the next token, and if t and et, are not null, t will
// be set to the start of the token and et to end of the token
int	gettoken(char **s, char *es, char **t, char **et)
{
	int	ret;

	while (*s < es && ft_strchr(WHITESPACE, **s))
		(*s)++;
	if (t)
		*t = *s;
	if (!**s)
		return (0);
	ret = ret_value(s, es);
	if (et)
		*et = *s;
	while (*s < es && ft_strchr(WHITESPACE, **s))
		(*s)++;
	return (ret);
}

int	argcount(char *s, char *es)
{
	int	argc;

	argc = 0;
	printf("argcount: enter\n");
	while (gettoken(&s, es, 0, 0) == 'a')
		argc++;
	printf("argcount: return\n");
	return (argc);
}
