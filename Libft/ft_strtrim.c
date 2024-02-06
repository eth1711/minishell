/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <antoinemalignon@yahoo.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:50:23 by amaligno          #+#    #+#             */
/*   Updated: 2024/02/06 15:42:29 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size(size_t a, size_t b, size_t len)
{
	size_t	exc;

	exc = a + b;
	if (exc > len)
		return (exc - len);
	else
		return (len - exc);
}

static size_t	strcheck(const char *c, char str)
{
	while (*c != '\0')
	{
		if (str == *c)
			return (1);
		c++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*cpy;
	size_t	len;
	size_t	back;
	size_t	front;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	back = 0;
	front = 0;
	len = ft_strlen(s1);
	while (strcheck(set, s1[front]))
		front++;
	while (strcheck(set, s1[(len - 1) - back]))
		back++;
	len = size(front, back, len);
	cpy = (char *)malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	back = 0;
	while (len--)
		cpy[back++] = s1[front++];
	cpy[back] = '\0';
	return (cpy);
}
