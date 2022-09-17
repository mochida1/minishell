/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 23:24:07 by coder             #+#    #+#             */
/*   Updated: 2022/09/17 23:34:28 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Counts the number of args in args and returns it. Really.
*/
int	count_args(char **args)
{
	int	i;

	i = 0;
	if (!args || !args[i])
		return (0);
	while (args[i])
		i++;
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
			if (ft_strlen(temp->content > PATH_MAX))
			{
				write (2, "cd: HOME too big to fit in here\n", 17);
				ms->exit_code = 1;
				return (NULL);
			}
			return (temp->content);
		}
		temp = temp->next;
	}
	write (2, "cd: HOME not set\n", 17);
	ms->exit_code = 1;
	return (NULL);
}
