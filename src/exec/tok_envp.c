/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 03:04:27 by coder             #+#    #+#             */
/*   Updated: 2022/09/21 03:05:27 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	count_envs(t_env_list *head)
{
	t_env_list *temp;
	int i;

	temp = head;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

/*
** Fills the temporary envp PP
*/
static void	tok_fill_envp(char **ret, t_env_list *head)
{
	int	i;

	i = 0;
	while (head)
	{
		ret[i] = ft_strdup(head->content);
		i++;
		head = head->next;
	}
}

/*
** Makes a PP of the envp again.
*/
char	**tok_envp(t_env_list *head)
{
	t_env_list	*temp;
	int			count;
	char		**ret;

	temp = head;
	count = count_envs(temp);
	if (!count)
		return (0);
	ret = ft_calloc(count, sizeof(char *));
	tok_fill_envp(ret, temp);
	return (ret);
}
