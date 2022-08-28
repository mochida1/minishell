/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:24:20 by coder             #+#    #+#             */
/*   Updated: 2022/08/28 21:28:02 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** wrapper for the given state
*/
int	prompt_state(t_ms_data *ms)
{
	int	rc;

	rc = set_prompt(ms);
	rc = get_data_from_readline(ms);
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
