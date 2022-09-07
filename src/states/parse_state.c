/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:38:58 by coder             #+#    #+#             */
/*   Updated: 2022/09/07 02:20:21 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Expande as variáveis dentro das splits;
*/
int	expand_variables(t_ms_data *ms)
{
	return (ms->state);
}

/*
** wrapper for the given state
*/
int	parse_state(t_ms_data *ms)
{
	ms->rl_spaced_buffer = add_spaces(ms->rl_buffer, ms);
	if (ms->set_buffer_to_null)
	{
		ms->rl_buffer = NULL;
	}
	ms->rl_split = ft_split_shell(ms->rl_spaced_buffer, ' ');
	assert (ms->rl_split);
	expand_variables(ms);
	ms->tokens = tokenize_splits(ms);
	categorize_tokens(ms->tokens);
	ms->state = EXECSTATE;
	return (0);
}
