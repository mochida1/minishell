/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:59:48 by coder             #+#    #+#             */
/*   Updated: 2022/09/24 22:37:59 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** executes the parsed and categorized commands
*/
int	exec_state(t_ms_data *ms/*, char **envp*/)
{
	t_com	*cmd;

	if (check_for_some_shady_shit(ms))
		return (-1);
	cmd = get_exec_info(ms);	
	if (!has_pipe(ms->tokens))
		exec_one_cmd(cmd, ms);
	// ms->exit_code = exec_MVP_TESTE(ms, envp);
	// print_token_list(ms);
	ms->state = CLEANSTATE;
	destroy_exec_info(cmd);
	return (0);
}
