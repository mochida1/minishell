/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 02:05:59 by coder             #+#    #+#             */
/*   Updated: 2022/10/05 01:04:56 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Checks if arg is a number.
*/
int	arg_is_number(char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

/*
** Sets minishell's shit to exit.
** also deals with bash's bullshit behaviour when using multiple commands.
*/
int	builtin_exit(char **args, char **envp, t_ms_data *ms)
{
	int	argc;

	(void) envp;
	argc = count_args(args);
	if (argc > 2 && arg_is_number(args[1]))
	{
		ms->exit_code = 1;
		printf("exit: too many arguments\n");
		return (1);
	}
	if (argc == 1)
		ms->exit_code = 0;
	else if (args[1] && !arg_is_number(args[1]))
	{
		printf ("exit\nexit: %s: numeric argument required\n", args[1]);
		ms->exit_code = 2;
	}
	else if (args[1] && arg_is_number(args[1]))
		ms->exit_code = ft_atoi(args[1]);
	ms->issue_exit = 1;
	return (ms->exit_code);
}
