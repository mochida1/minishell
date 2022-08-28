/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 01:58:25 by viferrei          #+#    #+#             */
<<<<<<< HEAD:src/main/minishell.c
/*   Updated: 2022/08/28 03:00:15 by viferrei         ###   ########.fr       */
=======
/*   Updated: 2022/08/28 23:27:31 by coder            ###   ########.fr       */
>>>>>>> origin/hm-mvp:src/minishell.c
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_ms_data	*ms;
	int			rc;

	ms = ft_calloc (1, sizeof(*ms));
	rc = 0;
	ms->state = 1;
	while (1)
	{
<<<<<<< HEAD:src/main/minishell.c
		buffer = readline("🦄 $> ");
=======
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
>>>>>>> origin/hm-mvp:src/minishell.c
	}
	return (0);
}
