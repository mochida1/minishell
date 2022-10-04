/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 01:58:25 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/05 01:41:36 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_ms_data	*ms;

	ms = ft_calloc (1, sizeof(t_ms_data));
	ms->state = INITSTATE;
	while (1)
	{
		if (ms->state <= ERRSTATE)
			error_state(ms);
		if (ms->state == INITSTATE)
			init_state(ms, argc, argv, envp);
		if (ms->state == PROMPTSTATE)
			prompt_state(ms);
		if (ms->state == PARSESTATE)
			parse_state(ms);
		if (ms->state == EXECSTATE)
			exec_state(ms);
		if (ms->state == CLEANSTATE)
			clean_state(ms);
	}
	return (0);
}
