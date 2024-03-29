/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:19:24 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/26 21:21:34 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	count;

	count = 0;
	toks->s++;
	if (*toks->s == '?')
	{
		*new = ft_safejoin(*new, ft_strdup("{exit_code_here}"));
		toks->s += 1;
		return ;
	}
	if (toks->s >= toks->es || (!(*toks->s >= 'a' && *toks->s <= 'z')
			&& !(*toks->s >= 'A' && *toks->s <= 'Z') && *toks->s != '_'))
	{
		*new = ft_safejoin(*new, ft_strdup("$"));
		// printf("expansion: expand_env: new: %s\n", *new);
		return ;
	}
	while ((toks->s + count) < toks->es && !ft_strchr("\'\" \n\t",
			toks->s[count]))
		count++;
	// printf("expansion: key: [");
	for (int i = 0; i < count; i++)
		printf("%c", toks->s[i]);
	// printf("]\n");
	*new = ft_safejoin(*new, ft_strdup(get_env(toks->s, env)));
	toks->s += count;
	// printf("expand_env: *new: %s\n", *new);
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
		// printf("expansion: toks.s[count]: %c\n", toks.s[count]);
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
