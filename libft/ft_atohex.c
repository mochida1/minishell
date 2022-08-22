/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:27:44 by viferrei          #+#    #+#             */
/*   Updated: 2022/02/22 19:51:53 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ctohex(char c)
{
	if (('0' <= c) && (c <= '9'))
		return (c - '0');
	else if (('A' <= c) && (c <= 'F'))
		return (10 + c - 'A');
	else if (('a' <= c) && (c <= 'f'))
		return (10 + c - 'a');
	return (0);
}

int	ft_atohex(const char *str)
{
	char	*hex_str;
	int		i;
	int		num;
	int		base;

	hex_str = ft_strchr(str, 'x');
	if (hex_str == NULL)
		hex_str = ft_strchr(str, 'X');
	if (hex_str == NULL)
		return (-1);
	num = 0;
	base = 1;
	i = ft_strlen(hex_str) - 1;
	while (i > 0)
	{
		num = num + ctohex(hex_str[i]) * base;
		base *= 16;
		i--;
	}
	return (num);
}
