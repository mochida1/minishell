/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:18:04 by coder             #+#    #+#             */
/*   Updated: 2022/09/25 21:41:47 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** wrapper for the given state
*/
int	error_state(t_ms_data *ms)
{
	int	exit_temp;
	int	should_exit;

	should_exit = ms->issue_exit;
	exit_temp = ms->exit_code;
	rl_clear_history ();
	ms->rl_buffer = safe_free(ms->rl_buffer);
	ms->rl_split = free_rl_split(ms);
	ms->home_original = safe_free(ms->home_original);
	ms->rl_prompt = safe_free (ms->rl_prompt);
	ms->tokens = destroy_token_list(ms);
	destroy_env_list(ms->env_head);
	ms = safe_free(ms);
	if (should_exit)
	{
		write (1, "exit\n", 6);
		exit(exit_temp);
	}
	exit (exit_temp * -1);
}
