/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaligno <amaligno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:39:35 by amaligno          #+#    #+#             */
/*   Updated: 2022/11/03 18:09:59 by amaligno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_char(char c, char *s)
{
	while (*s)
	{
		if (*s == c)
		{
			return (true);
		}
		s++;
	}
	return (false);
}

static bool	is_space(char c)
{
	return (is_char(c, "\t\n\v\f\r "));
}

static bool	is_operator(char c)
{
	return (is_char(c, "+-"));
}

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	if (is_operator(*str))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (is_digit(*str))
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	return (result * sign);
}

// int	main(int c, char **str)
// {
// 	int f = ft_atoi(str[1]);
// 	printf("%d", f);
// }