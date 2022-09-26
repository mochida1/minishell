/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:12:17 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/26 02:34:28 by viferrei         ###   ########.fr       */
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
			printf("export: '%s': not a valid identifier\n", head);
			return(0);
		}
		str++;
	}
	return (0);
}

// Returns 1 if the variable is already in the environment list 
int	var_exists(char *arg, t_env_list *env)
{
	t_env_list	*head;
	char		*var_name;

	head = env;
	var_name = get_var_name(arg);
	while (head)
	{
		if (vars_match(head->content, var_name))
		{
			free(var_name);
			return(1);
		}
		head = head->next;
	}
	free(var_name);
	return (0);
}

void	replace_var(char *arg, t_env_list *env)
{
	t_env_list	*head;
	char		*old_value;
	char		*var_name;

	head = env;
	var_name = get_var_name(arg);
	while (head)
	{
		if (vars_match(head->content, var_name))
		{
			old_value = head->content;
			head->content = ft_strdup(arg);
			free(old_value);
		}
		head = head->next;
	}
	free(var_name);
}

// Adds the variable to the environment list or replaces its value if it's
// already set
void	set_variable(char *arg, t_ms_data *ms)
{
	t_env_list	*head;

	head = ms->env_head;
	while (head->next)
		head = head->next;
	if (var_exists(arg, ms->env_head))
		replace_var(arg, ms->env_head);
	else
	{
		head->next = ft_calloc(1, sizeof(t_env_list));
		head = head->next;
		head->content = ft_strdup(arg);
	}
}

int		builtin_export(char	**args, t_ms_data *ms)
{
	if (!args)
	{
		printf("export: forgot something?\n");
		return(ms->exit_code);
	}
	while (*args)
	{
		if (equal_found(*args))
			set_variable(*args, ms);
		(args)++;
	}
	return(ms->exit_code);
}
