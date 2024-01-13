/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:32:18 by amaligno          #+#    #+#             */
/*   Updated: 2022/11/15 15:35:55 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(const char *str)
// {
// 	int		num;
// 	char	*ptr;

// 	num = 0;
// 	ptr = (char *)str;
// 	while (true)
// 	{
// 		if (*ptr == '\0')
// 			break ;
// 		ptr++;
// 		num++;
// 	}
// 	return (num);
// }

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (!dstsize)
		return (src_len);
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize < src_len)
		dst[dstsize - 1] = '\0';
	else if (dstsize != 0)
		dst[i] = '\0';
	return (src_len);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	char src[] = "coucou";
// 	char dest[10];

// 	printf("%lu\n", ft_strlcpy(dest, src, 6));
// 	printf("%s\n", dest);

// 	char src2[] = "coucou";
// 	char dest2[10];

// 	printf("%lu\n", strlcpy(dest2, src2, 6));
// 	printf("%s\n", dest2);

// }