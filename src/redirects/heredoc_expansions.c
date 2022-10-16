/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 19:13:45 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/16 19:34:41 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
static void	free_mouli(void *a, void *b)
{
	free(a);
	free(b);
	a = NULL;
	b = NULL;
}

char	*hd_update_exit_code(char *str, char *exit_code, char *var_head)
{
	char	*part1;
	char	*final_str;

	part1 = ft_strjoin(str, exit_code);
	final_str = ft_strjoin(part1, var_head + 2);
	free(part1);
	return (final_str);
}

// Handles "$?" expansions.
char	*hd_expand_exit_code(t_ms_data *ms, char *str)
{
	char		*v_head;
	char		*exit_str;
	char		*temp;

	while (1)
	{
		v_head = find_exit_code(str);
		if (v_head)
		{
			*v_head = '\0';
			exit_str = ft_itoa(ms->exit_code);
			temp = str;
			str = hd_update_exit_code(str, exit_str, v_head);
			free_mouli(exit_str, temp);
		}
		else
			break ;
	}
	return (str);
}

char *hd_update_str(char *str, char *var_name, char *var_head, t_ms_data *ms)
{
	char	*value;
	char	*part1;
	char	*final_str;
	void	*temp;

	temp = str;
	value = get_var_value(var_name, ms->env_head);
	if (!value)
		part1 = ft_strdup(str);
	else
		part1 = ft_strjoin(str, value);
	final_str = ft_strjoin(part1, var_head + 1 + ft_strlen(var_name));
	free(value);
	free(part1);
	free(temp);
	return (final_str);
}

char	*heredoc_handle_expansions(char *str, t_ms_data *ms)
{
	char	*var_head;
	char	*var_name;

	while (1)
	{
		var_head = find_variable(str);
		if (var_head)
		{
			var_name = get_var_name(var_head);
			*var_head = '\0';
			str = hd_update_str(str, var_name, var_head, ms);
			free(var_name);
		}
		else
			break ;
	}
	str = hd_expand_exit_code(ms, str);
	return (str);
}
