/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds_teste.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:31:47 by viferrei          #+#    #+#             */
/*   Updated: 2022/08/23 23:49:06 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**split_cmds(char *str);

int	main(void)
{
	char	*str;
	char	**cmds;

	str = "hey there \"this is a \'test test\' string\"";
	cmds = split_cmds(str);

	while (*cmds)
	{
		printf("%s", *cmds);
		cmds++;
	}
}