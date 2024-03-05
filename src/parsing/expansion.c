/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:19:24 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/05 21:13:01 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_safejoin(const char *s1, const char *s2)
{
	const char	*tmp;

	tmp = s1;
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
	char	*var;

	if (*(toks->s + 1) == '?' || (toks->s + 1) >= toks->es)
	{
		if (*(toks->s + 1) == '?')
			// expand_exit_code(*new , toks, env);
			ft_safejoin(*new, ft_strdup("[exit_code_here]"));
		else
			ft_safejoin(*new, ft_strdup("$"));
		return ;
	}
	count = 0;
	while ((toks->s + count) < toks->es && ft_strchr("\'\"$", toks->s[count]))
		count++;
	*new = ft_safejoin(*new, ft_strdup(get_env(toks->s, env, count)));
	toks->s += count;
}

void	expand(char **new, t_strptrs *toks, char *env)
{
	char	c;
	int		count;

	count = 0;
	c = *toks->s;
	
	while ((toks->s + count) < toks->es && (toks->s[count] != c && toks->s[count] != '$'))
		count++;
	*new = ft_safejoin(*new, ft_substr(toks->s, 0, count));
	toks->s += count;
	if (c != '\'' && *toks->s == '$')
		expand_env(new, toks, env);
}

void	expansion(t_strptrs toks, t_execcmd *exec, t_env *env)
{
	char	*new;
	char	*temp;
	int		count;

	count = 0;
	new = ft_strdup("");
	while ((toks.s + count) < toks.es)
	{
		while ((toks.s + count) < toks.es && !ft_strchr("\'\"$", toks.s[count]))
			count++;
		new = ft_safejoin(new, ft_substr(toks.s, 0, count));
		toks.s += count;
		if ((toks.s + count) < toks.es && ft_strchr("\'\"$", toks.s[count]))
			expand(&new, &toks, env);
		count = 0;
	}
	arg_add_back(&exec->args_list, args(new, toks.es, 1));
}