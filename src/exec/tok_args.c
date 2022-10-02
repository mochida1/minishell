/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 01:59:31 by coder             #+#    #+#             */
/*   Updated: 2022/10/02 22:45:40 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** counts the number of consecutive args and returns it;
*/
static int	tok_count_args(t_tokens *temp)
{
	t_tokens	*other;
	int			ret;

	other = temp;
	ret = 0;
	if (other && (other->type == COMTOKEN || other->type == BITOKEN))
	{
		ret++;
		other = other->next;
	}
	while (other && other->type == WORDTOKEN)
	{
		ret++;
		other = other->next;
	}
	return (ret);
}

/*
** Makes an orgy where all args are invited.
*/
char	**tok_args(t_ms_data *ms)
{
	t_tokens	*temp;
	char		**ret;
	int			count;
	int			i;

	count = 0;
	i = 0;
	temp = iterate_to_tok_index(ms);
	while (temp && (temp->type != COMTOKEN && temp->type != BITOKEN))
	{
		temp = temp->next;
		if (temp && temp->type == OPTOKEN)
			return (NULL);
	}
	if (!temp)
		return (NULL);
	count = tok_count_args(temp);
	ret = ft_calloc(count + 1, sizeof(char *));
	while (i < count)
	{
		ret[i] = ft_strdup(temp->value);
		temp = temp->next;
		i++;
	}
	return (ret);
}
