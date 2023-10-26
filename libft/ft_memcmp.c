/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:32:32 by amaligno          #+#    #+#             */
/*   Updated: 2022/10/24 14:31:12 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*ptr1;
	char	*ptr2;

	ptr1 = (char *)s1;
	ptr2 = (char *)s2;
	while (n--)
	{
		if (*ptr1 != *ptr2)
			return ((*(unsigned char *)ptr1 - *(unsigned char *)ptr2));
		ptr1++;
		ptr2++;
	}
	return (0);
}
