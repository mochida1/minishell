/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 21:11:37 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/26 01:23:58 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Returns the name of the variable.
char	*get_var_name(char	*var_head)
{
	size_t	len;

	len = 0;
	if (*var_head == '$')
		var_head++;
	while (var_head[len] && is_variable(var_head[len]))
		len++;
	return (ft_substr(var_head, 0, len));
}

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
