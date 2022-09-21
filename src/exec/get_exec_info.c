/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:12:55 by coder             #+#    #+#             */
/*   Updated: 2022/09/22 01:51:24 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Checks if token type at index is a PIPE
** returns 1 if it is, else returns 0;
*/
static int	tok_from_pipe(t_ms_data *ms)
{
	t_tokens	*temp;

	temp = iterate_to_tok_index(ms);
	if (temp->type == OPTOKEN)
		return (1);
	return (0);
}

/*
** Checks wether there's a pipe after the command block
*/
static int	tok_to_pipe(t_ms_data *ms)
{
	t_tokens	*temp;

	temp = iterate_to_tok_index(ms);
	if (temp && temp->type == OPTOKEN)
	{
		temp = temp->next;
		ms->token_index++;
	}
	while (temp)
	{
		if (temp->type == OPTOKEN)
		{
			return (1);
		}
		ms->token_index++;
		temp = temp->next;
	}
	return (0);
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
	self->red_in = tok_input(ms);
	self->red_out = tok_output(ms);
	self->envp = tok_envp(ms->env_head);
	self->sends_to_pipe = tok_to_pipe(ms);
	return (self);
}
