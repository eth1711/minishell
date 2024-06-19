/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value_splitter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:20:53 by amaligno          #+#    #+#             */
/*   Updated: 2024/06/19 18:16:10 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// splits given env string containing key value pair, into two seprate strings
// returns array of 2 strings, 0 is key, 1 is value
char	**key_value_splitter(char *string)
{
	int		count;
	char	**pair;

	if (!string)
		return (NULL);
	pair = malloc(sizeof(char *) * 2);
	pair[0] = NULL;
	count = 0;
	while (string[count] && string[count] != '=')
		count++;
	pair[0] = ft_substr(string, 0, count);
	string += count + 1;
	pair[1] = ft_substr(string, 0, ft_strlen(string));
	return (pair);
}
