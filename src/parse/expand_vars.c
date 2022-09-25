/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:40:14 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/25 20:00:16 by coder            ###   ########.fr       */
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
	while (env)
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

// Returns the string up to
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

// Updates the token if a variable is found.
void	if_variable(char *var_head, t_ms_data *ms)
{
	char	*var_name;

	var_name = get_var_name(var_head);
	*var_head = '\0';
	ms->tokens->value = update_token(ms, var_name, var_head);
	free(var_name);
}

// Iterates through tokens and expands their variables.
int	expand_variables(t_ms_data *ms)
{
	char		*var_head;
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
			if_variable(var_head, ms);
		else
			ms->tokens = ms->tokens->next;
	}
	ms->tokens = head;
	return (ms->state);
}
