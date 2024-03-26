/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:39:01 by amaligno          #+#    #+#             */
/*   Updated: 2024/03/26 21:15:01 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env(char *string, t_env *next)
{
	t_env	*new;
	int		count;

	count = 0;
	new = malloc(sizeof(t_env));
	while (string[count] && string[count] != '=')
		count++;
	new->key = ft_substr(string, 0, count);
	string += count + 1;
	new->value = ft_substr(string, 0, ft_strlen(string));
	new->next = next;
	return (new);
}

char	*get_env(char *key, t_env *envp)
{
	if (!envp)
		return (NULL);
	while (envp->next && ft_strcmp(envp->key, key))
		envp = envp->next;
	if (!ft_strcmp(envp->key, key))
		return (envp->value);
	return (printf("expansion: get_env: return nothing\n"), NULL);
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
