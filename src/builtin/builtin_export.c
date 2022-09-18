/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:12:17 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/18 20:12:36 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	export(char	**args, t_ms_data *ms)
{
	t_env_list	*head;

	head = ms->env_head;
	while (head->next)
		head = head->next;
	head->next = ft_calloc(1, sizeof(t_env_list));
	head = head->next;
	// head->content = 
	return(0);
}