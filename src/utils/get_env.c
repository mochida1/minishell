/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:38:27 by coder             #+#    #+#             */
/*   Updated: 2022/09/18 18:15:09 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Gets all eviromental variables and saves them in a list pointer;
** All things are allocated;
** It's the caller responsability do destroy the list after use;
*/
t_env_list	*get_env(char **envp)
{
	int			index;
	t_env_list	*self;
	t_env_list	*temp;

	index = 0;
	self = ft_calloc(1, sizeof(*self));
	temp = self;
	while (envp[index])
	{
		temp->content = ft_strdup(envp[index]);
		temp->next = ft_calloc(1, sizeof(*self));
		temp = temp->next;
		index++;
	}
	temp->next = safe_free(temp->next);
	return (self);
}

/*
** Destroys a MFing list;
** Also nullifies every content inside, because why not?
*/
void	*destroy_env_list(t_env_list *envs)
{
	t_env_list	*temp;
	t_env_list	*freeme;

	if (!envs)
		return (NULL);
	temp = envs;
	while (temp)
	{
		freeme = temp;
		temp = temp->next;
		freeme->content = safe_free(freeme->content);
		freeme = safe_free(freeme);
	}
	return (NULL);
}
