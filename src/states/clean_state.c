/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:06:20 by coder             #+#    #+#             */
/*   Updated: 2022/10/03 00:27:24 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	clean_state(t_ms_data *ms)
{
	if (ms->rl_buffer != ms->rl_spaced_buffer && ms->rl_spaced_buffer)
		ms->rl_spaced_buffer = safe_free(ms->rl_spaced_buffer);
	ms->tok_index = 0;
	ms->rl_buffer = safe_free(ms->rl_buffer);
	ms->rl_split = free_rl_split(ms);
	ms->tokens = destroy_token_list(ms);
	if (ms->issue_exit < 0)
	{
		ms->issue_exit = 0;
		ms->state = 0;
		return (0);
	}
	if (ms->issue_exit > 0)
	{
		ms->state = ERRSTATE;
		return (0);
	}
	else
	{
		ms->state = PROMPTSTATE;
		return (0);
	}
}
