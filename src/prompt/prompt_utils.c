/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:13:11 by coder             #+#    #+#             */
/*   Updated: 2022/08/28 22:09:05 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Sets the prompt to WHATEVER we want;
** and we want it pretty.
*/
int	set_prompt(t_ms_data *ms)
{
	ms->rl_prompt =  ft_strdup("\360\237\246\204 :) ");
	if (!(ms->rl_prompt))
		return (-1);
	return (0);
}

/*
** saves the result from readline in ms->rl_buffer;
** string must be freed before exiting program;
** returns 0 on sucess, 1 on error.
*/
int	get_data_from_readline(t_ms_data *ms)
{
	ms->rl_buffer = readline(ms->rl_prompt);
	if (ms->rl_buffer)
		return (0);
	else if (!(ms->rl_buffer))
		return (1);
	return (0);
}
