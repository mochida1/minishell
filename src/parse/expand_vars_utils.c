/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 21:11:37 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/19 00:36:38 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Returns the name of the variable.
char	*get_var_name(char	*var_head)
{
	size_t	len;

	len = 0;
	while (var_head[len] && is_variable(var_head[len + 1]))
		len++;
	return (ft_substr(var_head, 1, len));
}

// Finds the variable and returns its value.
char	*get_var_value(char *name, t_env_list *env)
{
	size_t	var_size;
	size_t	len;
	char	*str;
	char	*var_value;

	var_size = ft_strlen(name);
	var_value = NULL;
	len = 0;
	while (env->content)
	{
		str = env->content;
		if (ft_strnstr(str, name, var_size) && *(str + var_size) == '=')
		{
			while (*(str - 1) != '=')
				str++;
			while (str[len])
				len++;
			var_value = ft_substr(str, 0, len);
		}
		env = env->next;
	}
	return (var_value);
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
