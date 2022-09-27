/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 03:55:52 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/28 04:19:15 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	builtin_echo(char **args)
{
	int	newline;
	int	i;

	newline = 1;
	i = 0;
	if (!args)
	{
		printf("\n");
		return (0);
	}
	if (!ft_strcmp(args[i], "-n"))
	{
		newline = 0;
		i++;
	}
	while (args[i + 1])
	{
		printf("%s ", args[i]);
		i++;
	}
	if (args[i])
		printf("%s", args[i]);
	if (newline)
		printf("\n");
	return (0);
}
