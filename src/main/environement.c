/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:39:01 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/05 21:10:25 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env(char *string, t_env *next)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->string = ft_strdup(string);
	new->next = next;
	return (new);
}

char	*get_env(char *key, t_env *envp, int len)
{
	char	*ret;
	int		n;

	if (len >= 0)
		n = len;
	else
		n = ft_strlen(key);
	ret = envp->string;
	if (!envp)
		return (NULL);
	while (envp->next && ft_strncmp(key, ret, n))
		envp = envp->next;
	if (ft_strncmp(key, ret, n))
		return (NULL);
	while (*ret && *ret != '=')
		ret++;
	if (*ret == '=')
		ret++;
	return (ret);
}

void	put_env(char *string, t_env **envp)
{
	t_env	*new;

	if (!envp)
		return ;
	new = env(string, *envp);
	*envp = new;
}

t_env	*init_envp(char **envp)
{
	t_env	*head;

	while (*envp)
	{
		put_env(*envp, &head);
		envp++;
	}
	return (head);
}
