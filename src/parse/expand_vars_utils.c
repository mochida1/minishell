/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 21:11:37 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/05 00:13:31 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Returns 1 if both variables match
int	vars_match(char *env_var, char *var_name)
{
	size_t		var_size;
	var_size = ft_strlen(var_name);
	if (!ft_strncmp(env_var, var_name, var_size) && *(env_var + var_size) == '=')
		return (1);
	return (0);
}

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
