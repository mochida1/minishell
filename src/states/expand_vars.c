/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:40:14 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/06 23:54:04 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Iterates through string and sums the size of all variables started by "$"
size_t	get_names_size(char *str)
{
	size_t	size;

	size = 0;
	while (*str)
	{
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

// Returns the length of the variable values.
size_t	get_value_length(char *var_name, t_env_list *env)
{
	size_t	var_size;
	char	*str;
	size_t	len;

	var_size = ft_strlen(var_name);
	len = 0;
	while (env->content)
	{
		str = env->content;
		if(ft_strnstr(str, var_name, var_size) && *(str + 4) == '=')
		{
			while (*(str - 1) != '=')
				str++;
			while (*str)
			{
				len++;
				str++;
			}
		}
		env = env->next;
	}
	return(len);
}

// Parameter: a pointer to the "$" char.
// Return: an allocated string of the variable name, without the $.
char	*get_var_name(char *str)
{
	char	*begin;
	size_t	len;

	str++;
	begin = str;
	len = 0;
	while (!ft_isspace(*str) && !ft_isquote(*str) && *str)
	{
		len++;
		str++;
	}
	return(ft_substr(begin, 0, len));
}

// Matches each variable name with their value and returns the sum of the values
// length. Nonexistent variables count as 0.
size_t	get_values_size(char *str, t_env_list *env)
{
	char	*var_name;
	size_t	size;

	size = 0;
	while (*str)
	{
		if (*str == '$')
		{
			var_name = get_var_name(str);
			size += get_value_length(var_name, env);
			free(var_name);
		}
		str++;
	}
	return (size);
}

char	*get_var_value(char *var_name, t_env_list *env)
{
	size_t	var_size;
	size_t	len;
	char	*str;
	char	*var_value;

	var_size = ft_strlen(var_name);
	len = 0;
	while (env->content)
	{
		str = env->content;
		if(ft_strnstr(str, var_name, var_size) && *(str + var_size) == '=')
		{
			while (*(str - 1) != '=')
				str++;
			while(str[len])
				len++;
			var_value = ft_substr(str, 0, len);
		}
		env = env->next;
	}
	return (var_value);
}

void	copy_value(char *str, const char *value_name)
{
	int	i;

	i = 0;
	while (value_name[i])
		str[i] = value_name[i];
}

void	update_tokens(t_tokens *token, size_t final_size, t_env_list *env)
{
	char	*old_value;
	char	*var_name;
	char	*value_name;
	int		t;
	int		o;

	old_value = token->value;
	token->value = (char *) malloc(sizeof(char) * final_size);
	t = 0;
	o = 0;
	while (old_value[o])
	{
		while (old_value[o] && (old_value[o] != '$'))
			token->value[t++] = old_value[o++];
		if (old_value[o] == '$')
		{
			var_name = get_var_name(old_value);
			value_name = get_var_value(var_name, env);

			copy_value(&token->value[t], value_name);
			free(var_name);
			free(value_name);
			// while (!ft_isspace(old_value[o]) && !ft_isquote(old_value[o])
			// 		&& old_value[o])
			// 	o++;
		}
		if (old_value[o])
			o++;
	}
	free(old_value);
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
	size_t	final_size;

	while (ms->tokens)
	{
		if (ms->tokens->value[0] == '\'')
		{
			ms->tokens = ms->tokens->next;
			continue ;
		}
		str_size = ft_strlen(ms->tokens->value);
		names_size = get_names_size(ms->tokens->value);
		values_size = get_values_size(ms->tokens->value, ms->env_head);
		final_size = str_size - names_size + values_size + 1;
		update_tokens(ms->tokens, final_size, ms->env_head);
		test_expand_vars(ms->tokens->value, str_size, names_size, values_size);
		ms->tokens = ms->tokens->next;
	}
	return (ms->state);
}
