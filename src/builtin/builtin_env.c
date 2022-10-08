/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:50:18 by coder             #+#    #+#             */
/*   Updated: 2022/10/09 01:05:47 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	builtin_env(char **args, char **envp, t_env_list *env_list)
{
	t_env_list	*temp;

	(void) args;
	(void) envp;
	if (!env_list)
	{
		write (2, "Y u env when no env?\n", 21);
		return (127);
	}
	temp = env_list;
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
	temp = env_list;
	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
	return (0);
}
