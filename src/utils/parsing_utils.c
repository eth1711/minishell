/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:39:02 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/14 22:16:01 by amaligno         ###   ########.fr       */
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

//function that checks whether quotes are closed in a string
int	check_quotes(char *s, char *es)
{
	char	quote;

	while (s < es)
	{
		if (ft_strchr(QUOTES, *s))
		{
			quote = *s;
			s++;
			while (s < es && *s != quote)
				s++;
			if (*s != quote)
				return (0);
		}
		s++;
	}
	return (1);
}

//helper function for gettoken, that sets the value of ret
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
		while (*s < es && !ft_strchr(WHITESPACE, **s)
			&& !ft_strchr(SYMBOLS, **s))
		{
			if (ft_strchr(QUOTES, **s))
			{
				(*s)++;
				while (!ft_strchr(QUOTES, **s))
					(*s)++;
			}
			else
				(*s)++;
		}
	}
	return (ret);
}

// Function that 'gets' the next token it can find, the return value indicates
// the token found:
// 'a' indicates an argument of a command, LL and RR indicate
// << and >> respectively and any other character returned indicates that symbol
// 0 if it is the end of the string
// -1 if quotes are not closed
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

void	list_to_array(t_execcmd *exec)
{
	t_arg	*ptr;
	int		argc;

	argc = 0;
	ptr = exec->args_list;
	while (ptr)
	{
		argc++;
		ptr = ptr->next;
	}
	exec->args_array = malloc(sizeof(char *) * argc + 1);
	ptr = exec->args_list;
	argc = 0;
	while (ptr)
	{
		exec->args_array[argc++] = ptr->s;
		ptr = ptr->next;
	}
	exec->args_array[argc] = NULL;
}
