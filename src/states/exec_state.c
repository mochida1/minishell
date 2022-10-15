/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:59:48 by coder             #+#    #+#             */
/*   Updated: 2022/10/15 18:20:06 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	exec_loop(t_com *cmd, t_ms_data *ms, int original_fds[2])
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
		exec_one_cmd(cmd, ms, original_fds);
		return (0);
	}
	else if (!ms->issue_exit)
		return (exec_multi(cmd, ms, original_fds));
	return (1);
}

/*
** executes the parsed and categorized commands
*/
int	exec_state(t_ms_data *ms)
{
	t_com	*cmd;
	int		control;
	int		original_fds[2];

	control = 1;
	original_fds[0] = NO_REDIRECT;
	original_fds[1] = NO_REDIRECT;
	if (check_for_some_shady_shit(ms))
		return (-1);
	while (control)
	{
		cmd = get_exec_info(ms);
		expand_exit_code(ms, cmd->args);
		control = exec_loop(cmd, ms, original_fds);
		destroy_exec_info(cmd);
		if (ms->issue_exit)
			break ;
	}
	restore_original_fds(original_fds);
	ms->state = CLEANSTATE;
	return (0);
}
