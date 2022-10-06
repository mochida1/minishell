/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 01:58:25 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/06 04:45:42 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	check_for_args(int argc)
{
	if (argc > 1)
	{
		write(2, "you do not ARGue with minishell >:(\n", 36);
		exit (1);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_ms_data	*ms;

	check_for_args(argc);
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
