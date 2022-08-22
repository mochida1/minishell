/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 13:50:26 by viferrei          #+#    #+#             */
/*   Updated: 2021/08/27 16:55:43 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str != 0)
	{
		if (*str == (char)c)
			return ((char *) str);
		str++;
	}
	if (c == '\0')
		return ((char *) str);
	else
		return (0);
}
