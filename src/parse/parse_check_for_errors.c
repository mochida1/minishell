/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_for_errors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:37:21 by coder             #+#    #+#             */
/*   Updated: 2022/09/25 00:14:39 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Checks for open quotes in the string.
*/
static int	check_for_open_quotes(char *rl_buffer)
{
	int	i;
	int	sinquotes;
	int	douquotes;

	i = 0;
	sinquotes = 0;
	douquotes = 0;
	while (rl_buffer[i])
	{
		if (rl_buffer[i] == '\'' && (douquotes % 2 == 0))
			sinquotes++;
		if (rl_buffer[i] == '\"' && (sinquotes % 2 == 0))
			douquotes++;
		i++;
	}
	return ((sinquotes % 2) + (douquotes % 2));
}

/*
** Check for errors on the readline buffer. If true, frees it and sends back
** to the prompt state.
*/
int	parse_check_for_errors(t_ms_data *ms)
{
	int	error;

	error = check_for_open_quotes(ms->rl_buffer);
	if (error)
	{
		ms->rl_buffer = safe_free(ms->rl_buffer);
		ms->state = PROMPTSTATE;
		printf ("Close your motherfuckin quotes\n");
		return (1);
	}
	return (0);
}
