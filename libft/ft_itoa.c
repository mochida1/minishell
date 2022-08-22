/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:29:52 by viferrei          #+#    #+#             */
/*   Updated: 2022/02/16 15:47:39 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*writestr(char *str, int decimal, int n, int minus);
static char	*writemin(char *str);

static int	count_decimals(int n)
{
	int	count;
	int	minus;

	count = 0;
	minus = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		minus = 1;
		n = -n;
	}
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count + minus);
}

char	*ft_itoa(int n)
{
	int		minus;
	int		decimal;
	int		i_min;
	char	*str;

	minus = 0;
	decimal = count_decimals(n);
	i_min = 0;
	if (n == INT_MIN)
		i_min = 1;
	if (n < 0)
	{
		minus = 1;
		n = -n;
	}
	str = (char *) malloc(decimal + 1);
	if (!str || n > INT_MAX)
		return (0);
	if (i_min)
		return (writemin(str));
	return (writestr(str, decimal, n, minus));
}

static char	*writestr(char *str, int decimal, int n, int minus)
{
	str[decimal--] = '\0';
	while (decimal)
	{
		str[decimal--] = n % 10 + 48;
		n = n / 10;
	}
	if (minus)
		str[decimal] = '-';
	else
		str[decimal] = n % 10 + 48;
	return (str);
}

static char	*writemin(char *str)
{
	ft_strlcpy(str, "-2147483648", 12);
	return (str);
}
