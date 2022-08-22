/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert_xX_percent.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:17:46 by viferrei          #+#    #+#             */
/*   Updated: 2022/01/28 17:57:35 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrlen(unsigned long nbr);
static void		ft_revstring(char *str);

void	ft_convert_percent(t_holder *holder)
{
	holder->argument = malloc(sizeof(char));
	if (!holder->argument)
		return ;
	holder->argument[0] = '%';
	holder->len = 1;
}

void	ft_convert_x(t_format *fmt, t_holder *holder)
{
	unsigned long	nbr;

	nbr = (unsigned int)va_arg(fmt->arg, unsigned int);
	if (holder->specifier == 'x')
		holder->argument = ft_itoa_base(nbr, "0123456789abcdef");
	else
		holder->argument = ft_itoa_base(nbr, "0123456789ABCDEF");
	holder->len = ft_strlen(holder->argument);
}

char	*ft_itoa_base(unsigned long nbr, char *base)
{
	size_t	index;
	size_t	b_len;
	char	*str;

	index = 0;
	b_len = ft_strlen(base);
	if (nbr == 0)
		return (ft_strdup("0"));
	str = (char *)malloc(ft_nbrlen(nbr) + 1);
	if (!str)
		return (NULL);
	while (nbr > 0)
	{
		str[index++] = base[nbr % b_len];
		nbr /= b_len;
	}
	str[index] = '\0';
	ft_revstring(str);
	return (str);
}

static size_t	ft_nbrlen(unsigned long nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		len = 1;
	while (nbr > 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static void	ft_revstring(char *str)
{
	size_t		len;
	size_t		index;
	char		temp;

	index = 0;
	len = ft_strlen(str);
	while (index < len / 2)
	{
		temp = str[index];
		str[index] = str[len - 1 - index];
		str[len - 1 - index] = temp;
		index++;
	}
}
