/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:03:35 by amaligno          #+#    #+#             */
/*   Updated: 2022/11/14 16:33:12 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char			*f;
	unsigned char	r;

	r = c;
	if (r == '\0')
	{
		f = (char *)(str + ft_strlen(str));
		return (f);
	}
	while (*str != '\0')
	{
		if (*str == r)
		{
			f = (char *)str;
			return (f);
		}
		str++;
	}
	return (NULL);
}

/*int main(int c, char **str)
{
	char *f = ft_strchr(str[1], 'l');
	printf("%s", f);
}*/