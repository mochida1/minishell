/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:13:30 by coder             #+#    #+#             */
/*   Updated: 2022/10/05 01:11:03 by coder            ###   ########.fr       */
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
	ms->oldpwd = ft_strdup("");
	ms->home_original = ft_strdup(get_home_dir_from_envs(ms));
	return (0);
}

/*
** wrapper for the given state
*/
int	init_state(t_ms_data *ms, int argc, char *argv[], char **envp)
{
	int	rc;

	rc = shutup_unused_args(argc, argv[0][0]);
	rc = signal_handlers();
	rc = init_data(ms, envp);
	ms->state = PROMPTSTATE;
	if (rc)
		ms->state = ERRSTATE;
	return (rc);
}
