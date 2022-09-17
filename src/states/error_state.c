/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:18:04 by coder             #+#    #+#             */
/*   Updated: 2022/09/17 17:47:44 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** wrapper for the given state
*/
int	error_state(t_ms_data *ms)
{
	rl_clear_history ();
	destroy_env_list(ms->env_head);
	if (ms->issue_exit)
	{
		write (1, "exit\n", 6);
		exit(ms->exit_code);
	}
	exit (ms->state * -1);
}
