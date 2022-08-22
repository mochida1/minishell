/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_init_placeholder.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 18:46:38 by viferrei          #+#    #+#             */
/*   Updated: 2022/01/28 17:57:27 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Allocates memory and initializes the values of all the members in the
	structs t_format and t_holder.
*/

t_format	*ft_init_format(const char *format, va_list arg)
{
	t_format	*fmt;

	fmt = malloc(sizeof(t_format));
	if (!fmt)
		return (NULL);
	fmt->format = (char *)format;
	fmt->index = 0;
	va_copy(fmt->arg, arg);
	fmt->len = 0;
	return (fmt);
}

t_holder	*ft_init_holder(void)
{
	t_holder	*holder;

	holder = malloc(sizeof(t_holder));
	if (!holder)
		return (NULL);
	holder->argument = NULL;
	holder->specifier = '\0';
	holder->len = 0;
	return (holder);
}

/*
	FT_SPECIFIER
	Checks if the type passed to "%" is a valid type specifier and saves it to
	holder->specifier.

	FT_CONVERSIONS
	Sends the argument to be formatted to the appropriate conversion function.

	FT_PLACEHOLDER
	Prints the converted argument string.
*/

void	ft_placeholder(t_format *fmt, t_holder *holder)
{
	fmt->index++;
	ft_specifier(fmt, holder);
	if (holder->specifier)
	{
		ft_conversions(fmt, holder);
		fmt->len += write(1, holder->argument, holder->len);
		free(holder->argument);
	}
}

void	ft_specifier(t_format *fmt, t_holder *holder)
{
	if (ft_strchr("cspdiuxX%", fmt->format[fmt->index]))
		holder->specifier = fmt->format[fmt->index];
	else
		fmt->len += write(1, &fmt->format[fmt->index], 1);
	fmt->index++;
}

void	ft_conversions(t_format *fmt, t_holder *holder)
{
	if (holder->specifier == 'c')
		ft_convert_c(fmt, holder);
	if (holder->specifier == 'd' || holder->specifier == 'i')
		ft_convert_di(fmt, holder);
	if (holder->specifier == 'u')
		ft_convert_u(fmt, holder);
	if (holder->specifier == 's')
		ft_convert_s(fmt, holder);
	if (holder->specifier == '%')
		ft_convert_percent(holder);
	if (holder->specifier == 'p')
		ft_convert_p(fmt, holder);
	if (holder->specifier == 'x' || holder->specifier == 'X')
		ft_convert_x(fmt, holder);
}
