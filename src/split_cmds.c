/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:38:15 by viferrei          #+#    #+#             */
/*   Updated: 2022/08/27 23:04:04 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	contains_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
			return (1);
	}
	return (0);
}

//	Replaces the DELIMITER in-between quotes to the non-printable character -1
void	replace_between_quotes(char	*str, char delimiter)
{
	int	quote_type;

	quote_type = 0;
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
		{
			quote_type = *str;
			str++;
		}
		while (*str && quote_type)
		{
			if (*str == delimiter)
				*str = -1;
			if (*str == quote_type)
				quote_type = 0;
		}
		str++;
	}
}

//	Replaces every -1 in an array of strings to DELIMTER.
void	restore_delimiter(char **cmds, char delimiter)
{
	char	*str;

	while (*cmds)
	{
		str = *cmds;
		while (*str)
		{
			if (*str == -1)
				*str = delimiter;
			str++;
		}
		cmds++;
	}
}

//	Returns an array of strings with space as delimiter. Spaces between quotes
//	are ignored.
char	**split_cmds(char *str)
{
	char	**cmds;

	if (!contains_quotes(str))
		return (ft_split(str, ' '));
	replace_between_quotes(str, ' ');
	cmds = ft_split(str, ' ');
	restore_delimiter(cmds, ' ');
	return (cmds);
}
