/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:24:20 by coder             #+#    #+#             */
/*   Updated: 2022/09/11 00:31:23 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** wrapper for the given state
*/
int	prompt_state(t_ms_data *ms)
{
	int	rc;

	rc = get_data_from_readline(ms);
	if (ms->rl_buffer && ms->rl_buffer[0])
		add_history (ms->rl_buffer);
	assert(rc == 0);
	if (!rc)
	{
		ms->state = PARSESTATE;
		return (0);
	}
	if (rc)
		return (-1);
	return (0);
}
