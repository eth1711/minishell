/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:39:01 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/15 00:04:33 by amaligno         ###   ########.fr       */
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

	if (len < 0)
		len = ft_strlen(key);
	if (!envp)
		return (NULL);
	ret = envp->string;
	while (envp->next && ft_strncmp(key, ret, len))
	{
		ret = envp->string;
		envp = envp->next;
	}
	if (ft_strncmp(key, ret, len))
		return (ft_strdup(""));
	while (*ret && *ret != '=')
		ret++;
	if (*ret == '=')
		ret++;
	return (ret);
}

void	put_env(char *string, t_env **envp)
{
	t_env	*ptr;

	if (!envp)
		return ;
	if (!*envp)
	{
		*envp = env(string, NULL);
		return ;
	}
	ptr = *envp;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = env(string, NULL);
}

t_env	*init_envp(char **envp)
{
	t_env	*head;

	head = NULL;
	while (*envp)
	{
		put_env(*envp, &head);
		envp++;
	}
	return (head);
}
