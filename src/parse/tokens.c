/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 02:19:46 by coder             #+#    #+#             */
/*   Updated: 2022/09/07 02:29:44 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** saves tokens into a linked list;
** On success returns an address to the head of the list, else returns NULL.
*/
t_tokens	*tokenize_splits(t_ms_data *ms)
{
	int			i;
	t_tokens	*self;
	t_tokens	*temp;

	if (!ms->rl_split || !ms->rl_split[0])
		return (NULL);
	i = 0;
	self = ft_calloc(1, sizeof(*self));
	temp = self;
	while (ms->rl_split[i])
	{
		temp->value = ft_strdup(ms->rl_split[i]);
		if (ms->rl_split[i + 1])
			temp->next = ft_calloc(1, sizeof(*self));
		temp = temp->next;
		i++;
	}
	return (self);
}

/*
** Categoriza as tokens conforme os tipos
*/
void	categorize_tokens(t_tokens *tokens)
{
	t_tokens *temp;

	temp = tokens;
	while (temp)
	{
		temp->type = get_token_type(temp->value);
		temp = temp->next;
	}
}

int	get_token_type(char *value)
{
	int	ret;


	return (ret);
}
