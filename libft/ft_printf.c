/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:48:08 by viferrei          #+#    #+#             */
/*   Updated: 2022/01/28 17:57:20 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	size_t	len;

	va_start(arg, format);
	len = ft_vprintf(format, arg);
	va_end(arg);
	return (len);
}

int	ft_vprintf(const char *format, va_list arg)
{
	size_t		len;
	t_format	*fmt;
	t_holder	*holder;

	fmt = ft_init_format(format, arg);
	holder = ft_init_holder();
	while (fmt->format[fmt->index] != '\0')
	{
		if (fmt->format[fmt->index] == '%')
			ft_placeholder(fmt, holder);
		else
		{
			fmt->len += write(1, &fmt->format[fmt->index], 1);
			fmt->index++;
		}
	}
	len = fmt->len;
	free(fmt);
	free(holder);
	return (len);
}
