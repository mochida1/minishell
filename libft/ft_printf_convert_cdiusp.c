/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert_cdiusp.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:34:49 by viferrei          #+#    #+#             */
/*   Updated: 2022/01/28 17:57:40 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_convert_c(t_format *fmt, t_holder *holder)
{
	char	c;

	c = (int)va_arg(fmt->arg, int);
	holder->argument = malloc(sizeof(char));
	if (!holder->argument)
		return ;
	holder->argument[0] = c;
	holder->len = 1;
}

void	ft_convert_di(t_format *fmt, t_holder *holder)
{
	int		d;

	d = (int)va_arg(fmt->arg, int);
	holder->argument = ft_itoa(d);
	holder->len = ft_strlen(holder->argument);
}

void	ft_convert_u(t_format *fmt, t_holder *holder)
{
	unsigned int	u;

	u = (unsigned int)va_arg(fmt->arg, unsigned int);
	holder->argument = ft_uitoa(u);
	holder->len = ft_strlen(holder->argument);
}

void	ft_convert_s(t_format *fmt, t_holder *holder)
{
	holder->argument = ft_strdup(va_arg(fmt->arg, char *));
	if (!holder->argument)
		holder->argument = ft_strdup("(null)");
	holder->len = ft_strlen(holder->argument);
}

void	ft_convert_p(t_format *fmt, t_holder *holder)
{
	void	*ptr;
	char	*str;

	ptr = (void *)va_arg(fmt->arg, void *);
	str = ft_itoa_base((unsigned long) ptr, "0123456789abcdef");
	holder->argument = ft_strjoin("0x", str);
	holder->len = ft_strlen(holder->argument);
	free (str);
}
