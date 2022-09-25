/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:12:17 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/26 00:27:36 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../headers/minishell.h"

// Returns 1 if a '=' is found in the string
int	equal_found(char *str)
{
	char	*head;

	if (!*str)
		return (0);
	head = str;
	while (*str)
	{
		if (*str == '=')
			return (1);
		else if (!is_variable(*str))
		{
			printf("export: '%s': not a valid identifier", head);
			return(0);
		}
		str++;
	}
	return (0);
}

// Returns 1 if the variable already exists among environment list
// int	var_exists(char *str, t_env_list *env)
// {
	// get_var_name
// }

// Adds variable to the environment list if its value is set. Replaces it if
// needed
int	builtin_export(char	**args, t_ms_data *ms)
{
	t_env_list	*head;

	head = ms->env_head;
	while (head->next)
		head = head->next;
	if (!args)
	{
		printf("export: forgot something?\n");
		return(ms->exit_code);
	}
	while (*args)
	{
		// if (var_exists(*args, ms->env_head))
		// 	builtin_unset(args, ms);
		if (equal_found(*args))
		{
			head->next = ft_calloc(1, sizeof(t_env_list));
			head = head->next;
			head->content = ft_strdup(*args);
		}
		(args)++;
	}
	return(ms->exit_code);
}
