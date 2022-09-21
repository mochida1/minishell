/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:45:04 by coder             #+#    #+#             */
/*   Updated: 2022/09/22 01:57:00 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Uses getcwd to check for current working directory even is the env PWD is
** unset. Just like bash' pwd command.
*/
int	builtin_pwd(t_ms_data *ms)
{
	char	path_name[PATH_MAX];

	(void) args;
	if (!getcwd(path_name, PATH_MAX))
	{
		write (2, "Error: user is trying to fuck shit up!\n", 40);
		ms->exit_code = 1;
		return (1);
	}
	printf("%s\n", path_name);
	ms->exit_code = 0;
	return (0);
}
