/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:59:48 by coder             #+#    #+#             */
/*   Updated: 2022/10/05 01:45:51 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
	// else
	//	return (exec_multi(cmd, ms));
	return (1);
}

/*
** executes the parsed and categorized commands
*/
int	exec_state(t_ms_data *ms)
{
	t_com	*cmd;
	int		control;

	control = 1;
	if (check_for_some_shady_shit(ms))
		return (-1);
	while (control)
	{
		cmd = get_exec_info(ms);
		control = exec_loop(cmd, ms);
		destroy_exec_info(cmd);
	}
	ms->state = CLEANSTATE;
	return (0);
}
