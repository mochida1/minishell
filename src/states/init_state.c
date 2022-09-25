/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:13:30 by coder             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/24 22:36:24 by viferrei         ###   ########.fr       */
=======
/*   Updated: 2022/09/25 21:16:31 by coder            ###   ########.fr       */
>>>>>>> main
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
	// signal(SIGQUIT, SIG_IGN);
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
	ms->oldpwd = ft_strdup("");
	ms->home_original = ft_strdup(get_home_dir_from_envs(ms) + 5);
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
