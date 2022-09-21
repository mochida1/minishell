/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:12:17 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/21 02:28:26 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	export(char	**args, t_ms_data *ms)
{
	t_env_list	*head;
	(void) args;

	head = ms->env_head;
	while (head->next)
		head = head->next;
	head->next = ft_calloc(1, sizeof(t_env_list));
	head = head->next;
	// head->content =
	return(0);
}
