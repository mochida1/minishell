/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:40:45 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/02 22:49:08 by coder            ###   ########.fr       */
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
			return(1);
		head = head->next;
	}
	return(0);
}

// Returns the function of the first builtin found.
int	exec_builtin(t_com *cmd, t_ms_data *ms)
{
	if (!ft_strcmp(cmd->command, "echo"))
		return(builtin_echo(cmd->args));
	if (!ft_strcmp(cmd->command, "cd"))
		return(builtin_cd(cmd->args, cmd->envp, ms));
	if (!ft_strcmp(cmd->command, "pwd"))
		return(builtin_pwd(cmd->args, cmd->envp, ms));
	if (!ft_strcmp(cmd->command, "export"))
		return(builtin_export(cmd->args, ms));
	if (!ft_strcmp(cmd->command, "unset"))
		return(builtin_unset(cmd->args, ms));
	if (!ft_strcmp(cmd->command, "env"))
		return(builtin_env(cmd->args, cmd->envp, ms->env_head));
	if (!ft_strcmp(cmd->command, "exit"))
		return(builtin_exit(cmd->args, cmd->envp, ms));
	return(0);
}

// Handles single-command input - either builtin or not.
int	exec_one_cmd(t_com *cmd, t_ms_data *ms)
{
	// handle_redirects(ms);
	if (cmd->is_builtin)
		return(exec_builtin(cmd, ms));
	else
		ms->exit_code = exec_MVP_TESTE(cmd, ms);
	return (0);
}