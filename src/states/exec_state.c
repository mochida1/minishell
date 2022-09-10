/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:59:48 by coder             #+#    #+#             */
/*   Updated: 2022/09/10 23:01:07 by viferrei         ###   ########.fr       */
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
	ms->exit_code = exec_MVP_TESTE(ms, envp);
	print_token_list(ms);
	ms->state = CLEANSTATE;
	return (0);
}
