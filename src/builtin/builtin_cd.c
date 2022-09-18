/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:13:35 by coder             #+#    #+#             */
/*   Updated: 2022/09/18 02:24:48 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** If there's a PWD node inside the environmentals, updates it.
** return 0 on success and 1 on failure;
*/
static int	update_pwd(t_ms_data *ms, char *path)
{
	t_env_list	*temp;

	temp = ms->env_head;
	while (temp)
	{
		if (ft_strncmp (temp->content, "PWD=", 4))
		{
			temp->content = safe_free(temp->content);
			temp->content = ft_strjoin("PWD=", path);
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
		if (chdir(&home_path[5]))
		{
			write(2, "cd: something went terribly wrong\n", 34);
			return (2);
		}
		update_pwd(ms, &home_path[5]);
		return (0);
	}
	write (2, "cd: HOME not set\n", 17);
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
** returns a copy of the path, expanding ~'s
** returns NULL on failure;
*/
char	*expand_home(char *path, t_ms_data *ms)
{
	char	*home;

	if (path[0] != '~')
		return (ft_strdup(path));
	home = get_home_dir_from_envs(ms);
	if (!home)
		home = ms->home_original;
	return (ft_strjoin(home, path + 1));
}

/*
** Changes current PWD, if there's an env called PWD, updates it.
** On failure, prints the error and gets exit status > 0;
*/
int	builtin_cd(char **args, t_ms_data *ms)
{
	int		arg_number;
	char	*expanded_path;

	arg_number = count_args(args);
	if (arg_number == 0)
		ms->exit_code = cd_to_home(ms);
	if (arg_number > 1)
	{
		ms->exit_code = 1;
		write(2, "cd: too many freaking arguments", 32);
	}
	if (arg_number == 1)
	{
		expanded_path = expand_home(args[0], ms);
		if (ft_strlen(expanded_path) > PATH_MAX)
		{
			expanded_path = safe_free (expanded_path);
			write (2, "cd: path too big to fit in here\n", 17);
			return (1);
		}
		ms->exit_code = cd_to_path(expanded_path, ms);
		expanded_path = safe_free (expanded_path);
	}
	return (ms->exit_code);
}
