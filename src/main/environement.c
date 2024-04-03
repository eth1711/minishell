/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:39:01 by amaligno          #+#    #+#             */
/*   Updated: 2024/04/03 17:22:16 by amaligno         ###   ########.fr       */
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
	printf("expansion: get_env: key %s\n", key);
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
	new = malloc(sizeof(char *) * count + 1);
	new[count] = NULL;
	count = 0;
	ptr = envp;
	while (ptr)
	{
		tmp = ft_strjoin(ptr->key, "=");
		new[count] = ft_strjoin(tmp, ptr->value);
		free(tmp);
		ptr = ptr->next;
	}
	return (new);
}

t_env	*env_to_list(char **envp)
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
