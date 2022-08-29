/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:40:14 by viferrei          #+#    #+#             */
/*   Updated: 2022/08/29 19:41:26 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Iterates through string and sums the size of all variables started by "$"
size_t	get_names_size(char *str)
{
	size_t	size;

	size = 0;
	while (str)
	{
		if (*str == '$')
		{
			size++;
			str++;
			while (!ft_isspace(*str))
			{
				size++;
				str++;
			}
		}
		str++;
	}	
	return (size);
}

/*
** Expand variables;
** NOTE: try recursion for variables inside variables.
*/
int	expand_variables(t_ms_data *ms)
{
	size_t	buffer_size;
	// size_t	final_size;
	// size_t	names_size;
	// size_t	values_size;
	// char	*final_str;

	buffer_size = ft_strlen(ms->rl_buffer);
	// names_size = get_names_size(ms->rl_buffer);
	return (ms->state);
}
