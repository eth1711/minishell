/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:19:24 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/08 22:07:08 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_safejoin(char *s1, char *s2)
{
	char	*tmp;

	printf("ft_safejoin: *s1: %p\n", s1);
	tmp = s1;
	printf("ft_safejoin: *tmp: %p\n", tmp);
	
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	free(s2);
	return (s1);
}

// void	expand_exit_code(char **new, t_strptrs *toks, t_env *env)
// {
	
// }

void	expand_env(char **new, t_strptrs *toks, t_env *env)
{
	int		count;

	if (*(toks->s + 1) == '?')
	{
		//to be iplemented
		*new = ft_safejoin(*new, ft_strdup("[exit_code_here]"));
		toks->s += 17;
		return ;
	}
	if (*(toks->s + 1) > toks->es)
	{
		*new = ft_safejoin(*new, ft_strdup("$"));
		toks->s += 1;
		return ;
	}
	count = 0;
	while ((toks->s + count) < toks->es && ft_strchr("\'\"$", toks->s[count]))
		count++;
	*new = ft_safejoin(*new, ft_strdup(get_env(toks->s, env, count)));
	printf("expand_env: *new: %s\n", *new);
	toks->s += count;
}

void	expand_quotes(char **new, t_strptrs *toks, t_env *env)
{
	char	c;
	int		count;
	
	printf("expand: enter\n");
	count = 1;
	c = *toks->s;
	printf("expand: c: %c\n", c);
	while ((toks->s + count) < toks->es && toks->s[count] != c)
	{
		if (toks->s[count] == '$' && c != '\'')
		{
			*new = ft_safejoin(*new, ft_substr(toks->s, 0, count));
			toks->s += count;
			printf("expansion: new: %s\n", *new);
			expand_env(new, toks, env);
			count = 0;
		}
		count++;
	}
	*new = ft_safejoin(*new, ft_substr(toks->s, 0, count));
	toks->s += count;
}

void	expansion(t_strptrs toks, t_execcmd *exec, t_env *env)
{
	char	*new;
	int		count;

	printf("expansion: enter\n");
	count = 0;
	new = ft_strdup("");
	while ((toks.s + count) < toks.es)
	{
		while ((toks.s + count) < toks.es && !ft_strchr("\'\"$", toks.s[count]))
			count++;
		new = ft_safejoin(new, ft_substr(toks.s, 0, count));
		printf("expansion: new: %s\n", new);
		toks.s += count;
		if ((toks.s + count) < toks.es && ft_strchr("\'\"", toks.s[count]))
			expand_quotes(&new, &toks, env);
		else if ((toks.s + count) < toks.es && toks.s[count] =='$')
			expand_env(&new, &toks, env);
		count = 0;
	}
	arg_add_back(&exec->args_list, args(new, NULL));
}