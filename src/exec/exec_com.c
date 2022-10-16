/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmochida <hmochida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:15:32 by coder             #+#    #+#             */
/*   Updated: 2022/10/16 15:20:58 by hmochida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static pid_t	create_child(void)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
	{
		write(2, "error: Can't spawn child\n", 25);
		exit(-1);
	}
	return (child_pid);
}

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

int	exec_fork_builtin(t_com *cmd, t_ms_data *ms, int original_fds[2])
{
	int	pid;

	pid = create_child();
	if (!pid)
	{
		sig_defaults();
		if (handle_redirects(cmd, original_fds, ms))
		{
			ms->issue_exit = -1;
			return (restore_original_fds(original_fds));
		}
		ms->issue_exit = -1;
		return (exec_builtin(cmd, ms, original_fds));
	}
	return (ms->exit_code);
}

/*
** Executes a command.
*/
int	exec_com(t_com *cmd, t_ms_data *ms, int original_fds[2])
{
	int		pid;

	pid = create_child();
	if (!pid)
	{
		ms->exit_code = 0;
		if (!get_exec_error(cmd->command, ms))
		{
			sig_defaults();
			if (handle_redirects(cmd, original_fds, ms))
			{
				ms->issue_exit = -1;
				return (restore_original_fds(original_fds));
			}
			execve(cmd->command, cmd->args, cmd->envp);
		}
		else
			ms->issue_exit = -1;
		return (ms->exit_code);
	}
	return (ms->exit_code);
}
