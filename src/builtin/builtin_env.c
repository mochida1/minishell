/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:50:18 by coder             #+#    #+#             */
/*   Updated: 2022/08/27 22:56:23 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	builtin_env(t_env_list	*env_list)
{
	t_env_list	*temp;

	if (!env_list)
		return (1);
	temp = env_list;
	while (temp)
	{
		ft_printf("%s\n", temp->content);
		temp = temp->next;
	}
	return (0);
}
