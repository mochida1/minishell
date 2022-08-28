/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:24:20 by coder             #+#    #+#             */
/*   Updated: 2022/08/29 00:34:43 by coder            ###   ########.fr       */
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
