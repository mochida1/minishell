/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 23:19:44 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/12 14:43:16 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	handle_pipes(t_com *cmd, int original_output)
{
	static int	pipe_fds[2];

	if (cmd->receives_from_pipe)
	{
		dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
	}
	if (cmd->sends_to_pipe)
	{
		if (pipe(pipe_fds) == -1)
			printf("pipe error \n");
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
	}
	else
	{
		dup2(original_output, STDOUT_FILENO);
		close(original_output);
		return (0);
	}
	return (1);
}

int	exec_multi(t_com *cmd, t_ms_data *ms, int original_fds[2])
{
	int	control;

	if (original_fds[0] == NO_REDIRECT)
		original_fds[0] = dup(STDIN_FILENO);
	if (original_fds[1] == NO_REDIRECT)
		original_fds[1] = dup(STDOUT_FILENO);

	control = handle_pipes(cmd, original_fds[1]);
	exec_one_cmd(cmd, ms, original_fds);
	return (control);
}
