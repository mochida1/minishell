/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:13:30 by coder             #+#    #+#             */
/*   Updated: 2022/09/10 23:17:01 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** because yes.
*/
static int	shutup_unused_args(int delete, char me)
{
	return (delete + me);
}

/*
**
*/
int	init_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGTERM, sigterm_handler);
	signal(SIGQUIT, sigquit_handler);
	return (1);
}

/*
** sets prompt, get env variables from main;
** returns 0 on sucess, 1 on error.
*/
int	init_data(t_ms_data *ms, char **envp)
{
	set_prompt(ms);
	ms->env_head = get_env(envp);
	if (!ms->env_head)
		return (1);
	return (0);
}

/*
** wrapper for the given state
*/
int	init_state(t_ms_data *ms, int argc, char *argv[], char **envp)
{
	int	rc;

	rc = shutup_unused_args(argc, argv[0][0]);
	rc = init_signal_handlers();
	rc = init_data(ms, envp);
	ms->state = PROMPTSTATE;
	if (rc)
		ms->state = ERRSTATE;
	return (rc);
}
