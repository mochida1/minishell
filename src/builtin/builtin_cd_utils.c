/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 23:24:07 by coder             #+#    #+#             */
/*   Updated: 2022/10/06 02:00:52 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** returns a copy of the path, expanding ~'s
** returns NULL on failure;
*/
char	*expand_home(char *path, t_ms_data *ms)
{
	char	*home;

	if (path[0] != '~' && path[0] != '-')
		return (ft_strdup(path));
	if (path[0] == '-')
		return (ft_strdup(ms->oldpwd));
	home = get_home_dir_from_envs(ms);
	if (!home)
		home = ms->home_original;
	return (ft_strjoin(home, path + 1));
}

/*
** Counts the number of args in args and returns it. Really.
*/
int	count_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		i++;
	}
	return (i);
}

/*
** Gets HOME string address from env list.
** Returns the address of the string if it exists, else returns NULL.
*/
char	*get_home_dir_from_envs(t_ms_data *ms)
{
	t_env_list	*temp;

	temp = ms->env_head;
	while (temp)
	{
		if (!ft_strncmp (temp->content, "HOME=", 5))
		{
			if (ft_strlen(temp->content) > PATH_MAX)
			{
				write (2, "cd: HOME too big to fit in here\n", 17);
				ms->exit_code = 1;
				return (NULL);
			}
			return (temp->content + 5);
		}
		temp = temp->next;
	}
	ms->exit_code = 1;
	return (NULL);
}
