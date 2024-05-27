/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:19:24 by amaligno          #+#    #+#             */
/*   Updated: 2024/05/27 19:52:58 by amaligno         ###   ########.fr       */
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

// void	expand_exit_code(char **new, t_strptrs *toks, t_env *env)
// {
// }

void	expand_env(char **new, t_strptrs *toks, t_env *env)
{
	int		count;
	char	*key;

	count = 0;
	toks->s++;
	if (*toks->s == '?')
	{
		*new = ft_safejoin(*new, ft_itoa(WEXITSTATUS(g_error)));
		toks->s += 1;
		return ;
	}
	if (toks->s >= toks->es || (!(*toks->s >= 'a' && *toks->s <= 'z')
			&& !(*toks->s >= 'A' && *toks->s <= 'Z') && *toks->s != '_'))
	{
		*new = ft_safejoin(*new, ft_strdup("$"));
		return ;
	}
	while ((toks->s + count) < toks->es && !ft_strchr("\'\" \n\t$",
			toks->s[count]))
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

	// printf("expansion: expand_quotes: enter\n");
	count = 0;
	c = *toks->s++;
	while ((toks->s + count) < toks->es && toks->s[count] != c)
	{
		// printf("l72: expansion: expand_quotes: toks->s[count]%c\n", toks->s[count]);
		if (toks->s[count] == '$' && c != '\'')
		{
			*new = ft_safejoin(*new, ft_substr(toks->s, 0, count));
			toks->s += count;
			// printf("l77: expansion: expand_quotes: new: %s\n", *new);
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

	// printf("expansion: enter\n");
	count = 0;
	new = ft_strdup("");
	while ((toks.s + count) < toks.es)
	{
		while ((toks.s + count) < toks.es && !ft_strchr("\'\"$", toks.s[count]))
			count++;
		new = ft_safejoin(new, ft_substr(toks.s, 0, count));
		// printf("expansion: new: %s\n", new);
		toks.s += count;
		count = 0;
		// printf("expansion: count: %i\n", count);
		// if ((toks.s + count) >= toks.es)
			// printf("expansion: toks.s is more or equal to toks.es\n");
		if ((toks.s + count) < toks.es && ft_strchr("\'\"", toks.s[count]))
			expand_quotes(&new, &toks, env);
		else if ((toks.s + count) < toks.es && toks.s[count] == '$')
			expand_env(&new, &toks, env);
		count = 0;
	}
	if (exec)
		return(arg_add_back(&exec->args_list, args(new, NULL)), NULL);
	return (new);
}
