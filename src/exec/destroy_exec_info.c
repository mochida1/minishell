/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_exec_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 01:03:03 by coder             #+#    #+#             */
/*   Updated: 2022/09/22 01:34:39 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Frees the redirection list.
*/
static void	*free_red_list(t_reds *self)
{
	t_reds	*temp;

	temp = self;
	while (temp)
	{
		self = temp->next;
		temp->target = safe_free (temp->target);
		temp = safe_free (temp);
		temp = self;
	}
	return (self);
}

/*
** Use to free all stuff inside the given t_com struct.
** ie: self = destroy_exec_info(self);
*/
void	*destroy_exec_info(t_com *self)
{
	if (!self)
		return (NULL);
	if (self->command)
		self->command = safe_free(self->command);
	if (self->args)
		self->args = free_pp_char(self->args);
	if (self->envp)
		self->envp = free_pp_char(self->envp);
	if (self->error_to_print)
		self->error_to_print = safe_free(self->error_to_print);
	if (self->red_in)
		self->red_in = free_red_list(self->red_in);
	if (self->red_out)
		self->red_out = free_red_list(self->red_out);
	return (safe_free(self));
}
