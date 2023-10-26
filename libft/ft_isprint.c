/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:33:35 by amaligno          #+#    #+#             */
/*   Updated: 2022/10/21 18:06:24 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if ((c >= 32 && c <= 126))
		return (1);
	return (0);
}

/*int	main(int argc, char **argv)
{	
	int	f;

	if (argc != 2)
	{
		return(0);
	}
	f = ft_isprint(argv[1]);
	printf("%d", f);
}*/