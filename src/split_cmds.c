/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:38:15 by viferrei          #+#    #+#             */
/*   Updated: 2022/08/22 21:34:45 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//	Replaces the DELIMITER in-between quotes to the non-printable character -1
void	replace_between_quotes(char	*str, char delimiter)
{
	int	quote_type;
	
	quote_type = 0;
	while (*str)
	{
		if (*str == "\"" || *str == "\'")
		{
			quote_type = *str;
			str++;
		}
		while(*str && quote_type)
		{
			if(*str == delimiter)
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
			if (*cmds == -1)
				*cmds == delimiter;
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
		return(ft_split(str, " "));
	replace_between_quotes(str, " ");
	cmds = ft_split(str, " ");
	restore_delimiter(cmds, " ");
	return (cmds);
}