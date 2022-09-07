/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:40:14 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/08 00:59:36 by viferrei         ###   ########.fr       */
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

char *update_token(char *str, char *var_head)
{
	// char	*value;
	char	*part1;
	size_t	part1_len;

	part1_len = 0;
	while (str[part1_len] != *var_head)
		part1_len++;
	part1 = ft_substr(str, 0, part1_len);
	return();
}

// Iterates through tokens and expands their variables.
int	expand_variables(t_ms_data *ms)
{
	char	*var_head;
	int i = 1;

	while (ms->tokens)
	{
		if (ms->tokens->value[0] == '\'')
		{
			ms->tokens = ms->tokens->next;
			continue ;
		}
		var_head = find_variable(ms->tokens->value);
		if (i--)
		{
			ms->tokens->value = update_token(ms->tokens->value, var_head);
		}
		else
			ms->tokens = ms->tokens->next;
	}
	return (ms->state);
}
