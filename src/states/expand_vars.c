/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:40:14 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/09 02:08:53 by viferrei         ###   ########.fr       */
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

// Returns 
char	*update_token(t_ms_data *ms, char *var_name, char *var_head)
{
	char	*value;
	char	*part1;
	char	*final_str;

	value = get_var_value(var_name, ms->env_head);
	if (!value)
		part1 = ft_strdup(ms->tokens->value);
	else
		part1 = ft_strjoin(ms->tokens->value, value);
	final_str = ft_strjoin(part1, var_head + 1 + ft_strlen(var_name));
	free(value);
	free(part1);
	return (final_str);
}

// Iterates through tokens and expands their variables.
int	expand_variables(t_ms_data *ms)
{
	char		*var_head;
	char		*var_name;
	t_tokens	*head;
	size_t		var_len;

	var_len = 0;
	head = ms->tokens;
	while (ms->tokens)
	{
		if (ms->tokens->value[0] == '\'')
		{
			ms->tokens = ms->tokens->next;
			continue ;
		}
		var_head = find_variable(ms->tokens->value);
		if (var_head)
		{
			var_name = get_var_name(var_head);
			*var_head = '\0';
			ms->tokens->value = update_token(ms, var_name, var_head);
			free(var_name);
		}
		else
			ms->tokens = ms->tokens->next;
	}
	ms->tokens = head;
	test_expand_vars(ms);
	return (ms->state);
}
