/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:40:11 by amaligno          #+#    #+#             */
/*   Updated: 2022/11/16 12:26:45 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	allocsize(const char *s, size_t start, size_t len)
{
	if (ft_strlen(s) < len)
		return (ft_strlen(s) - start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	sub = malloc(sizeof(char) * (allocsize(s, start, len) + 1));
	i = 0;
	if (!sub)
		return (0);
	while ((*(s + start + i) != '\0') && (i < len))
	{
		sub[i] = *(s + start + i);
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

// int main(void)
// {
// 	char *s = ft_substr("tripouille", 0, 100);
// 	printf("%s$\n", s);
// }