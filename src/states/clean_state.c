/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:06:20 by coder             #+#    #+#             */
/*   Updated: 2022/09/26 00:38:26 by coder            ###   ########.fr       */
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
	if (ms->issue_exit)
	{
		printf ("EXIT ISSUED!\n");
		ms->state = ms->issue_exit;
		ms->env_head = destroy_env_list(ms->env_head);
		return (0);
	}
	else
	{
		ms->state = PROMPTSTATE;
		return (0);
	}
}
