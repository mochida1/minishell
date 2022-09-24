/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:12:17 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/24 22:09:17 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	export(t_ms_data *ms)
{
	t_env_list	*head;
	// (void) args;

	head = ms->env_head;
	while (head->next)
		head = head->next;
	head->next = ft_calloc(1, sizeof(t_env_list));
	head = head->next;
	// head->content =
	return(0);
}
