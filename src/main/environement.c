/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:39:01 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/19 18:53:02 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env(char *key, char *value, t_env *next)
{
	t_env	*new;
	int		count;

	count = 0;
	new = malloc(sizeof(t_env));
	new->key = key;
	new->value = value;
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
	return (NULL);
}

void	put_env(char *key, char *value, t_env **envp)
{
	t_env	*ptr;

	if (!envp)
		return ;
	if (!*envp)
	{
		*envp = env(key, value, NULL);
		return ;
	}
	ptr = *envp;
	while (ptr)
	{
		if (!ft_strcmp(key, ptr->key))
		{
			free(key);
			ptr->value = value;
			return ;
		}
		if (!ptr->next)
		{
			ptr->next = env(key, value, NULL);
			return ;
		}
		ptr = ptr->next;
	}
}

char	**env_to_array(t_env *envp)
{
	t_env	*ptr;
	char	*tmp;
	char	**new;
	int		count;

	ptr = envp;
	count = 0;
	while (ptr)
	{
		ptr = ptr->next;
		count++;
	}
	new = malloc(sizeof(char *) * (count + 1));
	new[count] = NULL;
	count = 0;
	ptr = envp;
	while (ptr)
	{
		tmp = ft_strjoin(ptr->key, "=");
		new[count] = ft_strjoin(tmp, ptr->value);
		free(tmp);
		count++;
		ptr = ptr->next;
	}
	return (new);
}

t_env	*env_to_list(char **envp)
{
	t_env	*head;
	char	**pair;

	head = NULL;
	while (*envp)
	{
		pair = key_value_splitter(*envp);
		put_env(pair[0], pair[1], &head);
		free(pair);
		envp++;
	}
	return (head);
}
