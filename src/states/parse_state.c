/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:38:58 by coder             #+#    #+#             */
/*   Updated: 2022/10/16 17:12:24 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	is_only_space(char *str)
{
	while (str)
	{
		if (!*str)
			return (1);
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

/*
** wrapper for the given state
*/
int	parse_state(t_ms_data *ms)
{
	if (parse_check_for_errors(ms))
		return (1);
	if (is_only_space(ms->rl_buffer))
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
	handle_variable_expansions(ms);
	categorize_tokens(ms->tokens);
	remove_quotes_from_tokens(ms->tokens);
	ms->state = EXECSTATE;
	return (0);
}
