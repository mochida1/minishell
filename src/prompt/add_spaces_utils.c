/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 02:20:50 by coder             #+#    #+#             */
/*   Updated: 2022/08/23 02:21:14 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** checa se o caractere é um operador que precisa de espaço no (mini)shell;
*/
int	is_operator(char c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (1);
	else if (c == '|')
		return (1);
	return (0);
}
