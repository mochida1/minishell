/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:05:53 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/21 02:10:52 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Frees environment list node if it matches unset argument
void	compare_arg_env(char *arg, t_env_list *head, t_env_list *tmp, 
						t_env_list *prev)
{
	if (!ft_strncmp(arg, head->content, ft_strlen(arg)))
	{
		if (!prev)
			tmp = head;
		else
		{
			prev->next = head->next;
			tmp = head;
		}
	}
	prev = head;
	head = head->next;
	safe_free(tmp);
}

int		builtin_unset(char	**args, t_ms_data *ms)
{	
	t_env_list	*head;
	t_env_list	*tmp;
	t_env_list	*prev;

	head = ms->env_head;
	tmp = NULL;
	prev = NULL;
	if (!args[1])
		return (0);
	while (*args)
	{
		while (head)
			compare_arg_env(*args, head, tmp, prev);
		*args++;	
	}
	return (0);
}