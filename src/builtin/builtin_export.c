/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:12:17 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/18 21:25:23 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	export(char	**args, t_ms_data *ms)
{
	t_env_list	*head;

	head = ms->env_head;
	while (head->next)
		head = head->next;
	if (!args)
		printf("export: forgot something?");
	while (**args)
	{
		head->next = ft_calloc(1, sizeof(t_env_list));
		head = head->next;
		head->content = ft_strdup(*args);
		(*args)++;
	}
	head->next = NULL;
	ms->exit_code = 0;
	return(ms->exit_code);
}