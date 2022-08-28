/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:38:58 by coder             #+#    #+#             */
/*   Updated: 2022/08/28 23:58:14 by coder            ###   ########.fr       */
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
** Expande as variáveis dentro das splits;
*/
int	expand_variables(t_ms_data *ms)
{
	return (ms->state);
}

/*
** Categoriza as tokens conforme os tipos
*/
void	categorize_tokens(t_tokens *tokens)
{
	assert (tokens != 0);
}

/*
** wrapper for the given state
*/
int	parse_state(t_ms_data *ms)
{
	ms->rl_spaced_buffer = add_spaces(ms->rl_buffer);
	ms->rl_split = ft_split_shell(ms->rl_spaced_buffer, ' ');
	assert (ms->rl_split);
	expand_variables(ms);
	ms->tokens = tokenize_splits(ms);
	categorize_tokens(ms->tokens);
	ms->state = EXECSTATE;
	return (0);
}
