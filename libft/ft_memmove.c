/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 19:16:14 by viferrei          #+#    #+#             */
/*   Updated: 2021/08/26 10:13:38 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_str;
	const char	*src_str;

	dst_str = dst;
	src_str = src;
	if (dst > src)
	{
		while (len--)
		{
			*(dst_str + len) = *(src_str + len);
		}
	}
	else
		ft_memcpy(dst_str, src_str, len);
	return (dst);
}
