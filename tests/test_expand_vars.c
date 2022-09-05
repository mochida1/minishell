/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 21:14:41 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/05 22:24:20 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	test_expand_vars(char *token, size_t str_size, size_t names_size, \
							size_t values_size)
{
	printf("\nToken: %s\n", token);
	printf("Total original str size: %zu\n", str_size);
	printf("Names size: %zu\n", names_size);
	printf("Values size: %zu\n\n", values_size);
}