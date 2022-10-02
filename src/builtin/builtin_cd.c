/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:13:35 by coder             #+#    #+#             */
/*   Updated: 2022/10/02 22:48:53 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** If there's an OLDPWD node inside the environmentals, updates it.
** return 0 on success. It should always be a success. But if not, returns 1.
*/
static int	update_oldpwd(t_ms_data *ms, char *curr_path)
{
	t_env_list	*oldpwd;

	oldpwd = ms->env_head;
	while (oldpwd)
	{
		if (ft_strncmp (oldpwd->content, "OLDPWD=", 7))
			break ;
		oldpwd = oldpwd->next;
	}
	ms->oldpwd = safe_free(ms->oldpwd);
	ms->oldpwd = ft_strdup(curr_path);
	if (oldpwd)
	{
		oldpwd->content = safe_free(oldpwd->content);
		oldpwd->content = ft_strjoin("OLDPWD=", ms->oldpwd);
		return (0);
	}
	return (1);
}

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
** If there's an OLDPWD env, updates it accordingly;
** On failure, prints the error and gets exit status > 0;
*/
int	builtin_cd(char **args, char **envp, t_ms_data *ms)
{
	int		arg_number;
	char	*expanded_path;

	(void) envp;
	arg_number = count_args(args);
	if (arg_number == 1)
		ms->exit_code = cd_to_home(ms);
	if (arg_number > 2)
	{
		write(2, "cd: too many freaking arguments\n", 32);
		return (ms->exit_code = 1);
	}
	if (arg_number == 2)
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
