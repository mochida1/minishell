/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:59:48 by coder             #+#    #+#             */
/*   Updated: 2022/10/10 02:47:21 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void exec_open_pipe(void)
{
}

int	exec_loop(t_com *cmd, t_ms_data *ms)
{
	if (!cmd)
		return (0);
	if (cmd->block_exec)
	{
		write (2, cmd->error_to_print, ft_strlen(cmd->error_to_print));
		return (0);
	}
	if (!cmd->receives_from_pipe && !cmd->sends_to_pipe)
	{
		exec_one_cmd(cmd, ms);
		return (0);
	}
	//else if(!ms->issue_exit)
	{
		ms->pipe_fd = pipe();
	//	return (exec_multi(cmd, ms));
	}
	return (1);
}

/*
** executes the parsed and categorized commands
*/
int	exec_state(t_ms_data *ms)
{
	t_com	*cmd;
	int		control;
	int		pipes;

	control = 1;
	pipes = 0;
	if (check_for_some_shady_shit(ms))
		return (-1);
	while (control)
	{
		cmd = get_exec_info(ms);
		control = exec_loop(cmd, ms);
		pipes = cmd->sends_to_pipe;
		destroy_exec_info(cmd);
		if (ms->issue_exit)
			break ;
	}
	if (pipes && !cmd && !ms->issue_exit)
		exec_open_pipe();
	ms->state = CLEANSTATE;
	return (0);
}
