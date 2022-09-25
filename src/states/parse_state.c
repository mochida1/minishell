/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:38:58 by coder             #+#    #+#             */
/*   Updated: 2022/09/25 22:21:42 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** wrapper for the given state
*/
int	parse_state(t_ms_data *ms)
{
	if (parse_check_for_errors(ms))
		return (1);
	if (!ms->rl_buffer[0])
	{
		ms->rl_spaced_buffer = NULL;
		ms->rl_split = NULL;
		ms->state = CLEANSTATE;
		return (0);
	}
	ms->rl_spaced_buffer = add_spaces(ms->rl_buffer, ms);
	if (ms->set_buffer_to_null)
		ms->rl_buffer = NULL;
	ms->rl_split = ft_split_shell(ms->rl_spaced_buffer, ' ');
	ms->tokens = tokenize_splits(ms);
	expand_variables(ms);
	categorize_tokens(ms->tokens);
	ms->state = EXECSTATE;
	return (0);
}
