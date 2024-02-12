/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:39:02 by amaligno          #+#    #+#             */
/*   Updated: 2024/02/12 17:59:16 by amaligno         ###   ########.fr       */
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

//function that expects **s to be either ' or ", then moves
//the local var ptr to the next one, 
int	quotes(char **s, char *es, char **t, char **et)
{
	char	c;
	char	*ptr;

	if (!s || !*s)
		return ;
	ptr = *s;
	*t = ptr;
	c = *ptr;
	while ((ptr < *es && *ptr) && *ptr != c)
		ptr++;
	if (*ptr == c)
		*et = ptr;
	else
		return (0);
	return (1);
}

void	list_to_array(t_execcmd *exec)
{
	int		i;
	t_arg	*head;

	i = 0;
	head = exec->args_list;
	exec->args_array = malloc (sizeof(char *) * arg_count(head));
	while (exec->args_array[i] && head->next)
	{
		head->es = '\0';
		exec->args_array[i] = head->s;
		head = head->next;
	}
}
