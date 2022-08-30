/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:31:47 by viferrei          #+#    #+#             */
/*   Updated: 2022/08/30 17:55:32 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	test_get_names_size()
{
	char	*str = "Hey $2345 there $789\"\n";

	printf("str: %s\n", str);
	printf("var names size sum: %zu\n", get_names_size(str));
}

void	test_add_spaces()
{
	char	*quote_redirect = "<< hi this is \" a test<<t\'o>>test\" >><\'< \">\'>|>> \'>>\'<<>>";

	printf("str: %s\n", quote_redirect);
	printf("add_spaces: %s\n", add_spaces(quote_redirect));
}

int	main(void)
{
	// test_get_names_size();
	test_add_spaces();
}
