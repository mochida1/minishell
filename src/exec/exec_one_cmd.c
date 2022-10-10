/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:40:45 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/10 02:46:43 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Returns 1 if a pipe operator is found.
int	has_pipe(t_tokens *tokens)
{
	t_tokens	*head;

	head = tokens;
	while (head)
	{
		if (head->type == OPTOKEN && !ft_strcmp(head->value, "|"))
			return (1);
		head = head->next;
	}
	return (0);
}

// Returns the function of the first builtin found.
int	exec_builtin(t_com *cmd, t_ms_data *ms)
{
	if (!ft_strcmp(cmd->command, "echo"))
		return (builtin_echo(cmd->args));
	if (!ft_strcmp(cmd->command, "cd"))
		return (builtin_cd(cmd->args, cmd->envp, ms));
	if (!ft_strcmp(cmd->command, "pwd"))
		return (builtin_pwd(cmd->args, cmd->envp, ms));
	if (!ft_strcmp(cmd->command, "export"))
		return (builtin_export(cmd->args, ms));
	if (!ft_strcmp(cmd->command, "unset"))
		return (builtin_unset(cmd->args, ms));
	if (!ft_strcmp(cmd->command, "env"))
		return (builtin_env(cmd->args, cmd->envp, ms->env_head));
	if (!ft_strcmp(cmd->command, "exit"))
		return (builtin_exit(cmd->args, cmd->envp, ms));
	return (0);
}

// Handles single-command input - either builtin or not.
int	exec_one_cmd(t_com *cmd, t_ms_data *ms)
{
	int	original_fds[2];

	original_fds[0] = NO_REDIRECT; //in original
	original_fds[1] = NO_REDIRECT; // out original

	// se receber de pipe abre a saida, dupa oringial_fd[0] para a saída do pipe, pipe[1];
	// se mandar para pipe, abre entrada do pipe, dupa original_fd[1] para a entrada do pipe, pipe[0].
	if (handle_redirects(cmd, original_fds, ms))
	{
		restore_original_fds(original_fds);
		return (1);
	}
	if (ms->issue_exit)
		return (ms->issue_exit);
	if (cmd->is_builtin)
		ms->exit_code = exec_builtin(cmd, ms);
	else
		ms->exit_code = exec_com(cmd, ms);
	// fecha a entrada do pipe
	// fecha a saida do pipe
	restore_original_fds(original_fds);
	return (0);
}
