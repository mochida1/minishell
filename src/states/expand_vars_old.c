/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_old.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:40:14 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/08 23:32:04 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// // Iterates through string and sums the size of all variables started by "$"
// size_t	get_names_size(char *str)
// {
// 	size_t	size;

// 	size = 0;
// 	while (*str)
// 	{
// 		if (*str == '$')
// 		{
// 			size++;
// 			str++;
// 			while (!ft_isspace(*str) && !ft_isquote(*str) && *str)
// 			{
// 				size++;
// 				str++;
// 			}
// 		}
// 		if (*str)
// 			str++;
// 	}
// 	return (size);
// }

// // Returns the length of the variable values.
// size_t	get_value_length(char *var_name, t_env_list *env)
// {
// 	size_t	var_size;
// 	char	*str;
// 	size_t	len;

// 	var_size = ft_strlen(var_name);
// 	len = 0;
// 	while (env->content)
// 	{
// 		str = env->content;
// 		if(ft_strnstr(str, var_name, var_size) && *(str + 4) == '=')
// 		{
// 			while (*(str - 1) != '=')
// 				str++;
// 			while (*str)
// 			{
// 				len++;
// 				str++;
// 			}
// 		}
// 		env = env->next;
// 	}
// 	return(len);
// }



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
	var_value = NULL;
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

size_t	copy_value(char *str, const char *value_name)
{
	int	i;

	i = 0;
	while (value_name[i])
	{
		str[i] = value_name[i];
		i++;
	}
	return (i);
}

void	update_tokens(t_ms_data *ms, size_t final_size)
{
	size_t	t;
	size_t	o;

	t = 0;
	o = 0;
	ms->expv->old = ms->tokens->value;
	ms->tokens->value = (char *) malloc(sizeof(char) * final_size);
	while (ms->expv->old[o])
	{
		while (ms->expv->old[o] && (ms->expv->old[o] != '$'))
			ms->tokens->value[t++] = ms->expv->old[o++];
		if (ms->expv->old[o] == '$')
		{
			ms->expv->name = get_var_name(&ms->expv->old[o]);
			ms->expv->value = get_var_value(ms->expv->name, ms->env_head);
			if (ms->expv->value != NULL)
				t += copy_value(&ms->tokens->value[t], ms->expv->value);
			safe_free(ms->expv->name);
			safe_free(ms->expv->value);
			while (!ft_isspace(ms->expv->old[o]) && ms->expv->old[o])
			{
				if (ft_isquote(ms->expv->old[o]))
					break ;
				o++;
			}
		}
	}
	free(ms->expv->old);
}

/*
** Expand variables;
** NOTE: try recursion for variables inside variables.
*/
int	expand_variables(t_ms_data *ms)
{
	// size_t	str_size;
	// size_t	names_size;
	// size_t	values_size;
	// size_t	final_size;

	while (ms->tokens)
	{
		if (ms->tokens->value[0] == '\'')
		{
			ms->tokens = ms->tokens->next;
			continue ;
		}
		// str_size = ft_strlen(ms->tokens->value);
		// names_size = get_names_size(ms->tokens->value);
		// values_size = get_values_size(ms->tokens->value, ms->env_head);
		// final_size = str_size - names_size + values_size + 1;
		// update_tokens(ms, final_size);
		// test_expand_vars(ms->tokens->value, str_size, names_size, values_size);

		

		ms->tokens = ms->tokens->next;
	}
	return (ms->state);
}
