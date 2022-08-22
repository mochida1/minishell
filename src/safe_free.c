/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:44:38 by coder             #+#    #+#             */
/*   Updated: 2022/08/22 02:57:30 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <stdlib.h>

int	safe_free (void *content)
{
	if (content)
	{
		free (content);
		content = NULL;
		return (0);
	}
	return (1);
}
