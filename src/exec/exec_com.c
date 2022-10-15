/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmochida <hmochida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:15:32 by coder             #+#    #+#             */
/*   Updated: 2022/10/15 18:09:02 by hmochida         ###   ########.fr       */
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
		printf("command not found!\n");
	}
	return (ms->exit_code);
}

int	exec_fork_builtin(t_com *cmd, t_ms_data *ms)
{
	ms->pid = create_child();
	ignore_signals();
	if (!ms->pid)
	{
		sig_defaults();
		ms->issue_exit = -1;
		return (exec_builtin(cmd, ms));
	}
	return (ms->exit_code >> 8);
}

/*
** execve para testes. deletar após implementar tudo direitinho
** pega o primeiro argumento da linha e usa como comando.
** retorna statsu de saída do filho
*/
int	exec_com(t_com *cmd, t_ms_data *ms)
{

	ms->pid = create_child();
	if (!ms->pid)
	{
		ms->exit_code = 0;
		if (!get_exec_error(cmd->command, ms))
		{
			sig_defaults();
			execve(cmd->command, cmd->args, cmd->envp);
		}
		else
		{
			ms->issue_exit = -1;
		}
		return (ms->exit_code);
	}
	return (ms->exit_code >> 8);
}
