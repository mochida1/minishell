/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:44:38 by coder             #+#    #+#             */
/*   Updated: 2022/08/24 02:55:12 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	safe_free(void *content)
{
	if (content)
	{
		free (content);
		content = NULL;
		return (0);
	}
	return (1);
}
