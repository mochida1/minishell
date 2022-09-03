/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:40:14 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/03 23:11:55 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Iterates through string and sums the size of all variables started by "$"
size_t	get_names_size(char *str, t_ms_data *ms)
{
	size_t	size;
	

	size = 0;
	while (*str)
	{
		if (*str == '\'')
			break ;
		if (*str == '$')
		{
			size++;
			str++;
			while (!ft_isspace(*str) && !ft_isquote(*str) && *str)
			{
				size++;
				str++;
			}
		}
		if (*str)
			str++;
	}
	return (size);
}

// Checks if the variable exists and returns the length of its value.
size_t	match_var_value(char *var_name, t_env_list *env)
{
	size_t	var_size;
	char	*str;
	size_t	len;

	var_size = ft_strlen(var_name);
	while (env)
	{
		str = env->content;	
		len = 0;
		if(ft_strnstr(str, var_name, var_size))
		{
			while (*str != '=')
				str++;
			while (*str)
				len++;
		}
		env = env->next;
	}
	return(0);
}

// Matches each variable name with their value and returns the sum of the values
// length. Nonexistent variables count as 0.
size_t	get_values_size(char *str, t_env_list *env)
{
	char	*var_name;
	char	*begin;
	size_t	len;
	size_t	size;

	size = 0;
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			begin = str;
			len = 0;
			while (!ft_isspace(*str) && !ft_isquote(*str) && *str)
			{
				len++;
				str++;
			}
			var_name = ft_substr(begin, 0, len);
			size = match_var_value(var_name, env)
			free(var_name);
		}
	}
	return (1);
}

/*
** Expand variables;
** NOTE: try recursion for variables inside variables.
*/
int	expand_variables(t_ms_data *ms)
{
	size_t	str_size;
	size_t	names_size;
	size_t	values_size;
	// size_t	final_size;
	// char	*final_str;

	while (ms->tokens)
	{
		str_size = ft_strlen(ms->tokens->value);
		names_size = get_names_size(ms->tokens->value, ms);
		if (!names_size)
		{
			ms->tokens = ms->tokens->next;
			continue ;
		}
		values_size = get_values_size(ms->tokens->value, ms->env_head);
		ms->tokens = ms->tokens->next;
	}
	return (ms->state);
}
