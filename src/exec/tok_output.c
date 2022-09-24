/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 02:58:01 by coder             #+#    #+#             */
/*   Updated: 2022/09/24 21:04:15 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** same as count_inputs, but with a different name
*/
static int	tok_count_outputs(t_tokens *arg_temp)
{
	t_tokens	*temp;
	int			ret;

	ret = 0;
	temp = arg_temp;
	if (temp && temp->type == OPTOKEN)
		temp = temp->next;
	while (temp && temp->type != OPTOKEN)
	{
		if (temp->type == REDTOKEN)
		{
			if (!ft_strcmp(">", temp->value))
				ret++;
			else if (!ft_strcmp(">>", temp->value))
				ret++;
		}
		temp = temp->next;
	}
	return (ret);
}

/*
** It fiils in the outlist. Quite the poet, eh?
*/
static void	tok_fill_outlist(t_reds *self, t_tokens *tokens)
{
	if (tokens && tokens->type == OPTOKEN)
		tokens = tokens->next;
	while (tokens && self && tokens->type != OPTOKEN)
	{
		if (tokens->type == REDTOKEN)
		{
			if (!ft_strcmp(">", tokens->value))
			{
				self->type = OVERWRITE;
				self->target = ft_strdup(tokens->next->value);
				self = self->next;
			}
			if (!ft_strcmp(">>", tokens->value))
			{
				self->type = APPEND;
				self->target = ft_strdup(tokens->next->value);
				self = self->next;
			}
		}
		tokens = tokens->next;
	}
}

/*
** If it goes in, it goes out.
*/
t_reds	*tok_output(t_ms_data *ms)
{
	t_tokens	*temp;
	t_reds		*self;
	int			count;

	temp = iterate_to_tok_index(ms);
	count = tok_count_outputs(temp);
	self = create_red_list(count);
	if (self)
		tok_fill_outlist(self, temp);
	return (self);
}
