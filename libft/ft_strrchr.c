/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 14:24:47 by viferrei          #+#    #+#             */
/*   Updated: 2021/09/08 19:26:37 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*str_end;
	char	ch;

	str_end = ft_strchr(str, '\0');
	ch = (unsigned char) c;
	if (ch == '\0')
		return (str_end);
	str_end--;
	while (*str != 0)
	{
		if (*str_end == ch)
			return (str_end);
		str++;
		str_end--;
	}
	return (NULL);
}
