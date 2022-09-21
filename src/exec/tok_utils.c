/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 03:01:41 by coder             #+#    #+#             */
/*   Updated: 2022/09/21 03:24:23 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Searches throught tokens untill it reaches ms->token_index.
** Returns a pointer to said node.
*/
t_tokens	*iterate_to_tok_index(t_ms_data *ms)
{
	t_tokens	*temp;

	temp = ms->tokens;
	while (temp && (temp->index != ms->token_index))
		temp = temp->next;
	return (temp);
}

/*
** Allocates space for the redirect list inside the command struct.
*/
t_reds	*create_red_list(int nodes)
{
	t_reds	*head;
	t_reds	*self;
	int		i;

	i = 0;
	if (!nodes)
		return (NULL);
	head = ft_calloc(1, sizeof(t_reds));
	self = head;
	while (i > nodes)
	{
		self->next = ft_calloc(1, sizeof(t_reds));
		i++;
		self = self->next;
	}
	return (head);
}
