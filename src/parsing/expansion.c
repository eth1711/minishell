/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:19:24 by amaligno          #+#    #+#             */
/*   Updated: 2024/07/03 16:09:41 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

void	expand_env(char **new, t_strptrs *toks, t_env *env, t_execcmd *exec)
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
	if (toks->s >= toks->es || (!ft_isalpha(*toks->s) && *toks->s != '_'))
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
	split_tokens(exec, new);
	free(key);
	toks->s += count;
}

void	expand_quotes(char **new, t_strptrs *toks, t_env *env, t_execcmd *exec)
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
			expand_env(new, toks, env, exec);
			count = 0;
		}
		else
			count++;
	}
	*new = ft_safejoin(*new, ft_substr(toks->s, 0, count));
	toks->s += count + 1;
}

//helper function to handle when inside heredoc, which ignores quotes
int	hdoc_quote(char c, int heredoc)
{
	if (heredoc)
		return (!ft_strchr("$", c));
	else
		return (!ft_strchr("\'\"$", c));
}

char	*expansion(t_strptrs toks, t_execcmd *exec, t_env *env, int heredoc)
{
	char	*new;
	int		count;

	count = 0;
	new = ft_strdup("");
	while ((toks.s + count) < toks.es)
	{
		while ((toks.s + count) < toks.es && hdoc_quote(toks.s[count], heredoc))
			count++;
		new = ft_safejoin(new, ft_substr(toks.s, 0, count));
		toks.s += count;
		count = 0;
		if ((toks.s + count) < toks.es && ft_strchr("\'\"", toks.s[count])
			&& !heredoc)
			expand_quotes(&new, &toks, env, exec);
		else if ((toks.s + count) < toks.es && toks.s[count] == '$')
			expand_env(&new, &toks, env, exec);
		count = 0;
	}
	if (exec)
		return (arg_add_back(&exec->args_list, args(new, NULL)), NULL);
	return (new);
}
