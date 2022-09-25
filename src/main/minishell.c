/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 01:58:25 by viferrei          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/23 21:49:26 by viferrei         ###   ########.fr       */
=======
/*   Updated: 2022/09/25 21:07:58 by coder            ###   ########.fr       */
>>>>>>> main
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
			exec_state(ms/*, envp*/);
		if (ms->state == CLEANSTATE)
			clean_state(ms);
	}
	return (0);
}
