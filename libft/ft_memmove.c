/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:33:26 by amaligno          #+#    #+#             */
/*   Updated: 2023/10/20 19:29:08 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *to, const void *from, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;

	if (!to && !from)
		return (NULL);
	d = (unsigned char *)to;
	s = (unsigned char *)from;
	if (d < s)
	{
		while (len--)
			*d++ = *s++;
	}
	else
	{
		d += len;
		s += len;
		while (len--)
			*--d = *--s;
	}
	return (to);
}

// int main(void)
// {
// 	char g[] = "34";
// 	char r[] = "123456789";
// 	char *s = ft_memmove(r, r + 2, 5);
// 	printf("%s", s);
// }