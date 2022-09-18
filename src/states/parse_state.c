/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:38:58 by coder             #+#    #+#             */
/*   Updated: 2022/09/19 00:51:49 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
	ms->tokens = tokenize_splits(ms);
	handle_variable_expansions(ms);
	categorize_tokens(ms->tokens);
	ms->state = EXECSTATE;
	return (0);
}
