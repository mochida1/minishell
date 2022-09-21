/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 02:58:01 by coder             #+#    #+#             */
/*   Updated: 2022/09/21 03:06:32 by coder            ###   ########.fr       */
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
	}
	return (ret);
}

/*
** It fiils in the outlist. Quite the poet, eh?
*/
static void	tok_fill_outlist(t_reds *self, t_tokens *tokens)
{
	t_tokens	*tempt;
	t_reds		*tempr;

	tempt = tokens;
	tempr = self;
	if (tempt && tempt->type == OPTOKEN)
		tempt = tempt->next;
	while (tempt && tempt->type != OPTOKEN)
	{
		if (tempt->type == REDTOKEN)
		{
			if (!ft_strcmp(">", tempt->value))
			{
				tempr->type = INFILE;
				tempr->target = ft_strdup(tempt->next->value);
			}
			else if (!ft_strcmp(">>", tempt->value))
			{
				tempr->type = HEREDOC;
				tempr->target = ft_strdup(tempt->next->value);
			}
			tempr = tempr->next;
		}
		tempt = tempt->next;
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
	count = tok_count_outputs(ms->tokens);
	self = create_red_list(count);
	if (self)
		tok_fill_outlist(self, temp);
	return (self);
}
