/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 21:14:41 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/09 02:06:37 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	test_expand_vars(t_ms_data *ms)
{
	t_tokens	*head;
	
	head = ms->tokens;
	while (ms->tokens)
	{
		printf("token: %s\n", ms->tokens->value);
		ms->tokens = ms->tokens->next;
	}
	ms->tokens = head;
}