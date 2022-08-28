/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 01:58:25 by viferrei          #+#    #+#             */
/*   Updated: 2022/08/28 03:23:34 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int set_prompt(t_ms_data *ms)
{
	ms->rl_prompt = "\360\237\246\204 :)";
	return (0);
}

int	get_data_from_readline(t_ms_data *ms)
{
	safe_free(ms->rl_buffer);
	ms->rl_buffer = readline(ms->rl_prompt);
	if (ms->rl_buffer)
		return (0);
	else if (!(ms->rl_buffer))
		return (1);
	else if (ms->rl_buffer < 0)
		return (-1);
	return (0);
}

int	update_data (t_ms_data *ms, char **envp)
{
	safe_free (ms->env_head);
	ms->env_head = get_env(envp);
	if (ms->env_head)
		return (0);
	ms->state++;
	return (1);
}

static int shutup_unused_args(int delete, char me)
{
	return (delete + me);
}

int	main(int argc, char *argv[], char **envp)
{
	t_ms_data *ms;
	int	rc;

	ms = ft_calloc (1, sizeof(*ms));
	rc = 0;
	ms->state = 0;
	while (!rc)
	{
		if (ms->state < 0)
			exit(ms->state * -1);
		if (ms->state == 0)
		{
			rc = update_data(ms, envp);
			rc = shutup_unused_args(argc, argv[0][0]);
		}
		if (ms->state == 1)
		{
			rc = set_prompt(ms);
			rc = get_data_from_readline(ms);
			if (rc)
				ms->state = 2;
		}
		if (ms->state == 2)
		{

		}

	}
	return (0);
}
