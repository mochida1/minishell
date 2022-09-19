/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:12:55 by coder             #+#    #+#             */
/*   Updated: 2022/09/19 02:43:50 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Checks if token type at index is a PIPE
** returns 1 if it is, else returns 0;
*/
int tok_from_pipe(t_ms_data *ms)
{
	t_tokens *temp;
	temp = iterate_to_tok_index(ms);
	if (temp->type == OPTOKEN)
		return (1);
	return (0);
}

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

int	tok_intype(t_ms_data *ms)
{
	t_tokens	*temp;
	int			ret;

	temp = iterate_to_tok_index(ms);
	ret = NOPE;
	while (temp && temp->type != OPTOKEN)
	{
		if (temp->type == REDTOKEN)
		{
			if (!ft_strcmp("<", temp->value))
				ret = INFILE;
			else if (!ft_strcmp("<<", temp->value))
				ret = HEREDOC;
		}
	}

}

/*
** Creates a struct that contains all the info used to execute a command or
** builtin command from minishell.
** Must be destroyed after use with destroy_exec_info(thisStruct);
*/
t_com	*get_exec_info(t_ms_data *ms)
{
	t_com	*self;

	self = ft_calloc(1, sizeof(t_com));
	self->receives_from_pipe = tok_from_pipe(ms);
	self->command = tok_command(ms, self);
	self->args = tok_args(ms);
	self->input_type = tok_intype(ms);
	self->sends_to_pipe = tok_to_pipe(ms); //AQUI ATUALIZA ms->index
	return (self);
}

