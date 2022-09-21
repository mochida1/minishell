/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 02:52:05 by coder             #+#    #+#             */
/*   Updated: 2022/09/22 00:48:44 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Counts the number of input redirects untill the next pipe
*/
static int	tok_count_inputs(t_tokens *arg_temp)
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
			if (!ft_strcmp("<", temp->value))
				ret++;
			else if (!ft_strcmp("<<", temp->value))
				ret++;
		}
		temp = temp->next;
	}
	return (ret);
}

/*
** Fills the input redirections list with the good stuff;
*/
static void	tok_fill_inlist(t_reds *self, t_tokens *tokens)
{
	if (tokens && tokens->type == OPTOKEN)
		tokens = tokens->next;
	while (tokens && self && tokens->type != OPTOKEN)
	{
		if (tokens->type == REDTOKEN)
		{
			if (!ft_strcmp("<", tokens->value))
			{
				self->type = INFILE;
				self->target = ft_strdup(tokens->next->value);
				self = self->next;
			}
			if (!ft_strcmp("<<", tokens->value))
			{
				self->type = HEREDOC;
				self->target = ft_strdup(tokens->next->value);
				self = self->next;
			}
		}
		tokens = tokens->next;
	}
}

/*
** makes a really noice list with all the inputs in a command block;
*/
t_reds	*tok_input(t_ms_data *ms)
{
	t_tokens	*temp;
	t_reds		*self;
	int			count;

	temp = iterate_to_tok_index(ms);
	count = tok_count_inputs(ms->tokens);
	self = create_red_list(count);
	if (self)
		tok_fill_inlist(self, temp);
	return (self);
}
