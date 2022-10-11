/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_remove_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 02:05:01 by coder             #+#    #+#             */
/*   Updated: 2022/10/10 02:12:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	remove_quotes_from_tokens(t_tokens *tokens)
{
	t_tokens	*temp;
	char		*trimmed;

	temp = tokens;
	while (temp)
	{
		if (temp->value[0] == '\"')
		{
			trimmed = ft_strtrim(temp->value, "\"");
			temp->value = safe_free(temp->value);
			temp->value = trimmed;
		}
		else if (temp->value[0] == '\'')
		{
			trimmed = ft_strtrim(temp->value, "\'");
			temp->value = safe_free(temp->value);
			temp->value = trimmed;
		}
		temp = temp->next;
	}
}