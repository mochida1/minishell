/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 23:19:44 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/10 02:27:10 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	handle_pipes(t_com *cmd, int original_fds[2])
{
	static int	pipe_fds[2];
	
	if (cmd->receives_from_pipe)
		dup2(pipe_fds[0], STDIN_FILENO);
	if (cmd->sends_to_pipe)
	{
		pipe(pipe_fds);
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
	}
	else
	{
		dup2(original_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
		return (0);
	}
	return (1);
}

int	exec_multi(t_com *cmd, t_ms_data *ms, int original_fds[2])
{
	int	control;

	control = handle_pipes(cmd, original_fds);
	exec_one_cmd(cmd, ms, original_fds);
	return (control);
}