/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:31:47 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/03 22:28:17 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	test_get_names_size()
{
	char	*str = "Hey $2345 there $789\"\n";

	printf("str: %s\n", str);
	printf("var names size sum: %zu\n", get_names_size(str));
}

void	test_get_values_size()
{
	char	*str = "Hey $2345 there $789\"\n";
	
}

int	main(void)
{
	test_get_names_size();
	test_get_values_size();
}
