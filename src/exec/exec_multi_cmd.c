/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 23:19:44 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/16 19:57:25 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	swap_pipes(t_ms_data *ms)
{
	static int	init;

	if (!init)
	{
		pipe(ms->pipe_out);
		init++;
	}
	ms->pipe_in[0] = ms->pipe_out[0];
	ms->pipe_in[1] = ms->pipe_out[1];
	pipe(ms->pipe_out);
	return (0);
}

int	exec_multi(t_com *cmd, t_ms_data *ms, int original_fds[2])
{
	int	control;

	if (original_fds[0] == NO_REDIRECT)
		original_fds[0] = dup(STDIN_FILENO);
	if (original_fds[1] == NO_REDIRECT)
		original_fds[1] = dup(STDOUT_FILENO);
	swap_pipes(ms);
	control = cmd->sends_to_pipe;
	if (ms->issue_exit)
		return (ms->issue_exit);
	if (cmd->is_builtin)
		ms->exit_code = exec_fork_builtin(cmd, ms, original_fds);
	else
		ms->exit_code = exec_com_multi(cmd, ms, original_fds);
	return (control);
}
