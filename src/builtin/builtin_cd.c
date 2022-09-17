/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:13:35 by coder             #+#    #+#             */
/*   Updated: 2022/09/17 23:30:10 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	update_pwd(t_ms_data *ms, char *path)
{
	t_env_list	*temp;

	temp = ms->env_head;
	while (temp)
	{
		if (ft_strncmp (temp->content, "PWD=", 4))
		{
			free (temp->content);
			temp->content = ft_strjoin ("PWD=", path);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

/*
** Changes dir to home and updates PWD;
** return 0 on success, and > 0 on error.
*/
static int	cd_to_home(t_ms_data *ms)
{
	char	*home_path;

	home_path = get_home_dir_from_envs(ms);
	if (home_path)
	{
		if (chdir(home_path[5]))
		{
			write(2, "cd: something went terribly wrong\n", 34);
			return (2);
		}
		update_pwd(ms, home_path[5]);
		return (0);
	}
	write (2, "cd: couldn't return to home\n", 28);
	return (1);
}

/*
** Changes dir to path and updates PWD;
** return 0 on success, and > 0 on error.
*/
static int	cd_to_path(char *path, t_ms_data *ms)
{
	if (!access(path, R_OK | F_OK))
	{
		if (chdir(path))
		{
			write(2, "cd: something went terribly wrong\n", 34);
			return (2);
		}
		update_pwd(ms, path);
		return (0);
	}
	write (2, "cd: couldnt go to ", 28);
	write (2, path, ft_strlen(path));
	write (2, "\n", 1);
	return (1);
}

/*
** Changes current PWD, if there's an env called PWD, updates it.
** On failure, prints the error and gets exit status > 0;
*/
int	builtin_cd(char **args, t_ms_data *ms)
{
	int	arg_number;

	arg_number = count_args(args);
	if (arg_number == 0)
		ms->exit_code = cd_to_home(ms);
	else if (arg_number == 1)
		ms->exit_code = cd_to_path(args[0], ms);
	else
	{
		ms->exit_code = 1;
		write(2, "cd: too many freaking arguments", 32);
	}
	return (ms->exit_code);
}
