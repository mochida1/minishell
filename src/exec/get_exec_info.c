/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:12:55 by coder             #+#    #+#             */
/*   Updated: 2022/09/28 01:33:57 by viferrei         ###   ########.fr       */
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
	if (temp && temp->type == OPTOKEN)
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
		ms->tok_index++;
	}
	while (temp)
	{
		if (temp->type == OPTOKEN)
		{
			return (1);
		}
		ms->tok_index++;
		temp = temp->next;
	}
	return (0);
}

/*
** return the last token index
*/
int	last_tok_index(t_ms_data *ms)
{
	t_tokens	*temp;
	int			ret;

	ret = 0;
	temp = ms->tokens;
	while (temp)
	{
		ret = temp->index;
		temp = temp->next;
	}
	return (ret);
}

/*
** Checks for errors that should block further execution.
** Updates error_to_print.
** Returns 1 if there are errors, else 0.
*/
int	check_for_errtokens(t_ms_data *ms, t_com *self)
{
	t_tokens	*temp;

	temp = ms->tokens;
	while (temp)
	{
		if (temp->type == ERRTOKEN)
		{
			self->block_exec = 1;
			self->error_to_print = ft_strdup("Invalid syntax, lear to ytpe.");
			return (1);
		}
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

	if (ms->tok_index > last_tok_index(ms))
		return (NULL);
	self = ft_calloc(1, sizeof(t_com));
	if (check_for_errtokens(ms, self))
		return(self);
	self->receives_from_pipe = tok_from_pipe(ms);
	self->command = tok_command(ms, self);
	self->args = tok_args(ms);
	self->red_in = tok_input(ms);
	self->red_out = tok_output(ms);
	self->envp = tok_envp(ms->env_head);
	self->sends_to_pipe = tok_to_pipe(ms);
	return (self);
}
