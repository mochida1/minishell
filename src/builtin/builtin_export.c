/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:12:17 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/21 00:55:58 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Returns 1 if a '=' is found in the string
int	equal_found(char *str)
{
	size_t	len;
	char	*head;
	char	*name;

	if (!*str)
		return (0);
	head = str;
	while (*str)
	{
		if (!is_variable(*str))
		{
			printf("export: '%s': not a valid identifier", head);
			return(0);
		}
		if(*str == '=')
			return (1);
		*str++;
	}
	return (0);
}

// Adds variable to the environment list if its value is set 
int	export(char	**args, t_ms_data *ms)
{
	t_env_list	*head;

	head = ms->env_head;
	while (head->next)
		head = head->next;
	if (!args[1])
		printf("export: forgot something?");
	while (*args)
	{
		if (equal_found(*args))
		{
			head->next = ft_calloc(1, sizeof(t_env_list));
			head = head->next;
			head->content = ft_strdup(*args);
		}
		(*args)++;
	}
	head->next = NULL;
	ms->exit_code = 0;
	return(ms->exit_code);
}