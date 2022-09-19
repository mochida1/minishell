/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:44:38 by coder             #+#    #+#             */
/*   Updated: 2022/09/19 00:39:21 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	*safe_free(void *content)
{
	if (content != NULL)
	{
		free (content);
		content = NULL;
		return (NULL);
	}
	return (NULL);
}

void	*free_rl_split(t_ms_data *ms)
{
	int	i;

	i = 0;
	if (!ms->rl_split)
		return (NULL);
	while (ms->rl_split[i])
	{
		ms->rl_split[i] = safe_free(ms->rl_split[i]);
		i++;
	}
	ms->rl_split = safe_free(ms->rl_split);
	return (NULL);
}

void	*destroy_token_list(t_ms_data *ms)
{
	t_tokens	*freeme;

	if (!ms->tokens)
		return (NULL);
	while (ms->tokens)
	{
		freeme = ms->tokens;
		safe_free(freeme->value);
		freeme->value = NULL;
		ms->tokens = ms->tokens->next;
		safe_free(freeme);
		freeme = NULL;
	}
	return (NULL);
}

/*
** Frees and sets to NULL an array of strings;
*/
void	*free_pp_char(char **pp)
{
	int	i;

	i = 0;
	while (pp[i])
	{
		pp[i] = safe_free (pp[i]);
		i++;
	}
	pp = safe_free(pp);
	return (NULL);
}
