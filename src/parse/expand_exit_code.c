/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:38:52 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/05 01:42:13 by viferrei         ###   ########.fr       */
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

// Returns the position of "$?"
char	*find_exit_code(char *str)
{
	while (*str)
	{
		if (*str == '$' && str[1] == '?')
			return (str);
		str++;
	}
	return (NULL);
}

// NOTE: TEST IF IT WORKS WITH $? AT THE END OF STRING.
char	*update_token_exit_code(char *str, char *exit_code, char *var_head)
{
	char	*part1;
	char	*final_str;

	part1 = ft_strjoin(str, exit_code);
	final_str = ft_strjoin(part1, var_head + 2);
	free(part1);
	return (final_str);
}

// Handles "$?" expansions.
void	expand_exit_code(t_ms_data *ms)
{
	char		*v_head;
	char		*exit_str;
	char		*temp;
	t_tokens	*head;

	head = ms->tokens;
	while (head)
	{
		if (head->value[0] == '\'')
		{
			head = head->next;
			continue ;
		}
		v_head = find_exit_code(head->value);
		if (v_head)
		{
			*v_head = '\0';
			exit_str = ft_itoa(ms->exit_code);
			temp = head->value;
			head->value = update_token_exit_code(head->value, exit_str, v_head);
			free_mouli(exit_str, temp);
		}
		else
			head = head->next;
	}
}
