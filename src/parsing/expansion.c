/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:19:24 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/20 16:35:27 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

char	*ft_safejoin(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	if (tmp)
		free(tmp);
	if (s2)
		free(s2);
	return (s1);
}

void	expand_env(char **new, t_strptrs *toks, t_env *env)
{
	int		count;
	char	*key;

	count = 0;
	toks->s++;
	if (*toks->s == '?')
	{
		*new = ft_safejoin(*new, ft_itoa(g_error));
		toks->s += 1;
		return ;
	}
	if (toks->s >= toks->es || (!(*toks->s >= 'a' && *toks->s <= 'z')
			&& !(*toks->s >= 'A' && *toks->s <= 'Z') && *toks->s != '_'))
	{
		*new = ft_safejoin(*new, ft_strdup("$"));
		return ;
	}
	while ((toks->s + count) < toks->es
		&& !ft_strchr("\'\" \n\t$", toks->s[count])
		&& (ft_isalnum(toks->s[count]) || toks->s[count] == '_'))
		count++;
	key = ft_substr(toks->s, 0, count);
	*new = ft_safejoin(*new, ft_strdup(get_env(key, env)));
	free(key);
	toks->s += count;
}

void	expand_quotes(char **new, t_strptrs *toks, t_env *env)
{
	char	c;
	int		count;

	count = 0;
	c = *toks->s++;
	while ((toks->s + count) < toks->es && toks->s[count] != c)
	{
		if (toks->s[count] == '$' && c != '\'')
		{
			*new = ft_safejoin(*new, ft_substr(toks->s, 0, count));
			toks->s += count;
			expand_env(new, toks, env);
			count = 0;
		}
		else
			count++;
	}
	*new = ft_safejoin(*new, ft_substr(toks->s, 0, count));
	toks->s += count + 1;
}

char	*expansion(t_strptrs toks, t_execcmd *exec, t_env *env)
{
	char	*new;
	int		count;

	count = 0;
	new = ft_strdup("");
	while ((toks.s + count) < toks.es)
	{
		while ((toks.s + count) < toks.es && !ft_strchr("\'\"$", toks.s[count]))
			count++;
		new = ft_safejoin(new, ft_substr(toks.s, 0, count));
		toks.s += count;
		count = 0;
		if ((toks.s + count) < toks.es && ft_strchr("\'\"", toks.s[count]))
			expand_quotes(&new, &toks, env);
		else if ((toks.s + count) < toks.es && toks.s[count] == '$')
			expand_env(&new, &toks, env);
		count = 0;
	}
	if (exec)
		return (arg_add_back(&exec->args_list, args(new, NULL)), NULL);
	return (new);
}
