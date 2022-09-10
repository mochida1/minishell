/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 21:11:37 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/10 22:14:32 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Checks if the char is acceptable in a variable name.
int	is_variable(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

// Returns a pointer to the first occurence of a variable in the string.
char	*find_variable(char	*str)
{
	while (*str)
	{
		if (*str == '$' && is_variable(str[1]))
			return (str);
		str++;
	}
	return (NULL);
}
