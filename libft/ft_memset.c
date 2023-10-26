/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:15:15 by amaligno          #+#    #+#             */
/*   Updated: 2022/10/18 15:51:33 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*s;

	s = (char *)b;
	i = -1;
	while (++i < len)
	{
		s[i] = c;
	}
	return (b);
}

/*int main(void)
{
	int	a = 'h';
	char c[] = "hello";
	int f[6] = {1,2,3,4,5,6};
	int *d = ft_memset(f, 0, 3);
}*/