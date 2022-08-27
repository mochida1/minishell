/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:31:47 by viferrei          #+#    #+#             */
/*   Updated: 2022/08/27 23:19:27 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**split_cmds(char *str);

int	main(void)
{
	char	*str;
	char	*temp;
	char	**cmds;

	str = "<< hi this is \" a test<<to>>test\" >><< >>>> \'>>\'<<>>";
	temp = add_spaces(str);
	cmds = split_cmds(temp);

	while (*cmds)
	{
		printf("%s", *cmds);
		cmds++;
	}
}
