/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:50:18 by coder             #+#    #+#             */
/*   Updated: 2022/10/09 01:16:11 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_for_path(t_env_list *env_list)
{
	t_env_list	*temp;

	temp = env_list;
	if (!env_list)
	{
		write (2, "Y u env when no env?\n", 21);
		return (127);
	}
	while (temp)
	{
		if (!ft_strncmp(temp->content, "PATH=", 5))
			break ;
		temp = temp->next;
	}
	if (!temp)
	{
		write(2, "env: No such file or directory\n", 31);
		return (127);
	}
	return (0);
}

int	builtin_env(char **args, char **envp, t_env_list *env_list)
{
	t_env_list	*temp;
	int			rc;

	(void) args;
	(void) envp;
	temp = env_list;
	rc = check_for_path(env_list);
	if (rc)
		return (rc);
	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
	return (0);
}
