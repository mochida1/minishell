/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:13:30 by coder             #+#    #+#             */
/*   Updated: 2022/09/08 00:45:34 by viferrei         ###   ########.fr       */
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
	rc = init_data(ms, envp);
	ms->state = PROMPTSTATE;
	if (rc)
		ms->state = ERRSTATE;
	return (rc);
}
