/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:59:48 by coder             #+#    #+#             */
/*   Updated: 2022/09/21 03:48:06 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** executes the parsed and categorized commands
*/
int	exec_state(t_ms_data *ms, char **envp)
{
	if (check_for_some_shady_shit(ms))
		return (-1);
	if (!has_pipe(ms->tokens))
		exec_one_cmd(ms);
	ms->exit_code = exec_MVP_TESTE(ms, envp);
	print_token_list(ms);
	ms->state = CLEANSTATE;
	return (0);
}
