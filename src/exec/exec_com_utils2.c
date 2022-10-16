/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_com_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmochida <hmochida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 19:03:47 by hmochida          #+#    #+#             */
/*   Updated: 2022/10/16 19:06:34 by hmochida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	get_exec_error(char *path, t_ms_data *ms)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		ms->exit_code = 126;
		printf("Is a directory!\n");
	}
	if (!path)
		ms->exit_code = 1;
	else if (access(path, X_OK))
	{
		ms->exit_code = 127;
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": command not found!\n", STDERR_FILENO);
	}
	return (ms->exit_code);
}

int	pipe_handle(t_ms_data *ms, t_com *cmd)
{
	if (cmd->receives_from_pipe)
	{
		close(ms->pipe_in[1]);
		dup2(ms->pipe_in[0], STDIN_FILENO);
	}
	if (cmd->sends_to_pipe)
	{
		close(ms->pipe_out[0]);
		dup2(ms->pipe_out[1], STDOUT_FILENO);
	}
	return (0);
}
