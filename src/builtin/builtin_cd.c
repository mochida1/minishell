/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:13:35 by coder             #+#    #+#             */
/*   Updated: 2022/10/09 01:03:40 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Changes dir to home and updates PWD;
** return 0 on success, and > 0 on error.
*/
static int	cd_to_home(t_ms_data *ms)
{
	char	*home_path;
	char	curr_path[PATH_MAX];

	getcwd(curr_path, PATH_MAX);
	home_path = get_home_dir_from_envs(ms);
	if (home_path)
	{
		if (chdir(home_path))
		{
			write(2, "cd: something went terribly wrong\n", 34);
			return (2);
		}
		update_oldpwd(ms, curr_path);
		update_pwd(ms, home_path);
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
	char	curr_path[PATH_MAX];

	getcwd(curr_path, PATH_MAX);
	if (!access(path, R_OK | F_OK))
	{
		if (chdir(path))
		{
			write(2, "cd: something went terribly wrong\n", 34);
			return (2);
		}
		update_oldpwd(ms, curr_path);
		getcwd(curr_path, PATH_MAX);
		update_pwd(ms, curr_path);
		return (0);
	}
	write (2, "cd: couldnt go to ", 18);
	write (2, path, ft_strlen(path));
	write (2, "\n", 1);
	return (1);
}

static int	cd_to_tilde(char **args, t_ms_data *ms)
{
	char	*expanded_path;

	expanded_path = expand_home(args[1], ms);
	if (ft_strlen(expanded_path) > PATH_MAX)
	{
		expanded_path = safe_free (expanded_path);
		write (2, "cd: path too big to fit in here\n", 17);
		return (1);
	}
	ms->exit_code = cd_to_path(expanded_path, ms);
	expanded_path = safe_free (expanded_path);
	return (ms->exit_code);
}

static int	cd_to_oldpwd(int print, t_ms_data *ms)
{
	char	oldcwd[PATH_MAX];
	char	cwd[PATH_MAX];

	getcwd(oldcwd, PATH_MAX - 1);
	if (chdir(ms->oldpwd))
	{
		write(2, "cd: can't go back to where you haven't been\n", 44);
		return (2);
	}
	if (print)
	{
		ft_putstr_fd(ms->oldpwd, 1);
		write(1, "\n", 1);
	}
	getcwd(cwd, PATH_MAX -1);
	update_oldpwd(ms, oldcwd);
	update_pwd(ms, cwd);
	return (0);
}

/*
** Changes current PWD, if there's an env called PWD, updates it.
** If there's an OLDPWD env, updates it accordingly;
** On failure, prints the error and gets exit status > 0;
*/
int	builtin_cd(char **args, char **envp, t_ms_data *ms)
{
	int		arg_number;

	(void) envp;
	arg_number = count_args(args);
	if (arg_number == 1)
		ms->exit_code = cd_to_home(ms);
	if (arg_number > 2)
		return (cd_error_args(ms));
	if (arg_number == 2)
	{
		if (args[1][0] == '~' && args[1][1] != '-')
			ms->exit_code = cd_to_tilde(args, ms);
		else if (args[1][0] == '-' && !args[1][1])
			ms->exit_code = cd_to_oldpwd(1, ms);
		else if (args[1][0] == '~' && args[1][1] == '-')
			ms->exit_code = cd_to_oldpwd(0, ms);
		else if (args[1][0] == '-' && args[1][1])
		{
			write (2, "CD: No options allowed brah\n", 28);
			ms->exit_code = 1;
		}
		else
			ms->exit_code = cd_to_path(args[1], ms);
	}
	return (ms->exit_code);
}
