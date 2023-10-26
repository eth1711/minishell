/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:19:34 by amaligno          #+#    #+#             */
/*   Updated: 2022/10/25 17:45:10 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	move(const char *s1, const char *s2, char *str)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		str[i] = *s2;
		i++;
		s2++;
	}
	str[i] = '\0';
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t		len;
	char		*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = (ft_strlen(s1) + ft_strlen(s2));
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	move(s1, s2, str);
	return (str);
}

/*size_t main(size_t c, char **str)
{
	char *s = ft_strjoin(str[1], str[2]);
	printf("%s", s);
}*/