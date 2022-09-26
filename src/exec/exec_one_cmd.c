/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:40:45 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/26 02:39:00 by viferrei         ###   ########.fr       */
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

// Returns 1 upon the first builtin found.
int	is_builtin(t_tokens *tokens)
{
	t_tokens	*head;

	head = tokens;
	while (head)
	{
		if (head->type == BITOKEN)
		{
			if (!ft_strcmp(head->value, "echo")
				|| !ft_strcmp(head->value, "cd")
				|| !ft_strcmp(head->value, "pwd")
				|| !ft_strcmp(head->value, "export")
				|| !ft_strcmp(head->value, "unset")
				|| !ft_strcmp(head->value, "env")
				|| !ft_strcmp(head->value, "exit"))
				return(1);
		}
		head = head->next;
	}
	return(0);
}

// Returns the function of the first builtin found.
int	exec_builtin(t_com *cmd, t_ms_data *ms)
{
	t_tokens	*head;

	head = ms->tokens;
	while (head)
	{
		if (head->type == BITOKEN)
		{
			// if (!ft_strcmp(head->value, "echo"))
			// 	return(builtin_echo(ms));
			// if (!ft_strcmp(head->value, "cd"))
			// 	return(builtin_cd(ms));
			// if (!ft_strcmp(head->value, "pwd"))
			// 	return(builtin_pwd(ms));
			if (!ft_strcmp(head->value, "export"))
				return(builtin_export(cmd->args, ms));
			if (!ft_strcmp(head->value, "unset"))
				return(builtin_unset(cmd->args, ms));
			if (!ft_strcmp(head->value, "env"))
				return(builtin_env(ms->env_head));
			// if (!ft_strcmp(head->value, "exit"))
			// 	return(builtin_exit(ms));
		}
		head = head->next;
	}
	return(0);
}

// Handles single-command input - either builtin or not.
int	exec_one_cmd(t_com *cmd, t_ms_data *ms)
{
	handle_redirects(ms);
	if (is_builtin(ms->tokens))
		return(exec_builtin(cmd, ms));
	else
		;
		// fork_exec_one_cmd(ms);
	return (0);
}
