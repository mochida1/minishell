/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:05:53 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/06 01:58:07 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Frees environment list node if it matches unset argument
void	compare_arg_env(char *arg, t_ms_data *ms)
{
	t_env_list	*head;
	t_env_list	*tmp;

	if (!arg)
		return ;
	if (ms->env_head && vars_match(ms->env_head->content, arg))
	{
		tmp = ms->env_head;
		ms->env_head = ms->env_head->next;
		free(tmp->content);
		free(tmp);
	}
	head = ms->env_head;
	while (head && head->next)
	{
		if (vars_match(head->next->content, arg))
		{
			tmp = head->next;
			head->next = head->next->next;
			safe_free(tmp->content);
			safe_free(tmp);
		}
		else
			head = head->next;
	}
}

int	builtin_unset(char **args, t_ms_data *ms)
{	
	if (!args[1])
		return (0);
	args ++;
	while (*args)
	{
		compare_arg_env (*args, ms);
		args++;
	}
	return (0);
}
