/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:19:24 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/19 17:10:58 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_safejoin(char *s1, char *s2)
{
	char	*tmp;

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
	int	count;

	count = 0;
	toks->s++;
	if (*toks->s == '?')
	{
		//to be iplemented
		*new = ft_safejoin(*new, ft_strdup("{exit_code_here}"));
		toks->s += 1;
		return ;
	}
	if (toks->s >= toks->es || (!(*toks->s >= 'a' && *toks->s <= 'z') &&
		!(*toks->s >= 'A' && *toks->s <= 'Z')))
	{
		*new = ft_safejoin(*new, ft_strdup("$"));
		printf("expansion: expand_env: new: %s\n", *new);
		return ;
	}
	while ((toks->s + count) < toks->es && !ft_strchr("\'\"", toks->s[count]))
		count++;
	printf("expansion: key: [");
	for (int i = 0; i < count; i++)
		printf("%c", toks->s[i]);
	printf("]\n");
	*new = ft_safejoin(*new, ft_strdup(get_env(toks->s, env, count)));
	toks->s += count;
	printf("expand_env: *new: %s\n", *new);
}

void	expand_quotes(char **new, t_strptrs *toks, t_env *env)
{
	char	c;
	int		count;

	printf("expansion: expand_quotes: enter\n");
	count = 0;
	c = *toks->s++;
	while ((toks->s + count) < toks->es && toks->s[count] != c)
	{
		if (toks->s[count] == '$' && c != '\'')
		{
			*new = ft_safejoin(*new, ft_substr(toks->s, 0, count));
			toks->s += count;
			printf("expansion: expand_quotes: new: %s\n", *new);
			expand_env(new, toks, env);
			count = 0;
		}
		else
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
		else if ((toks.s + count) < toks.es && toks.s[count] == '$')
			expand_env(&new, &toks, env);
		count = 0;
	}
	arg_add_back(&exec->args_list, args(new, NULL));
}
