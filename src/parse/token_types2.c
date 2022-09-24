/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:38:57 by coder             #+#    #+#             */
/*   Updated: 2022/09/24 21:54:23 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	token_is_error(t_tokens *temp)
{
	if (temp->type == OPTOKEN && (!ft_strcmp(temp->value, "||")))
		return (1);
	if (temp->type == OPTOKEN && !temp->prev)
		return (1);
	if (temp->prev && temp->prev->type == REDTOKEN)
		if (temp->type == OPTOKEN || temp->type == REDTOKEN)
			return (1);
	if (temp->prev && temp->prev->type == OPTOKEN)
		if (temp->type == OPTOKEN)
			return (1);
	if (temp->type == REDTOKEN && !temp->next)
		return (1);
	return (0);
}

int	token_is_fd(t_tokens *temp)
{
	if (temp->prev && temp->prev->type == REDTOKEN)
		return (1);
	return (0);
}
