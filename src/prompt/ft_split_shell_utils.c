/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmochida <hmochida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 05:04:52 by hmochida          #+#    #+#             */
/*   Updated: 2022/10/15 05:47:21 by hmochida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Quite literally iterates through the quotes.
*/
void	iterate_through_quotes(t_split_shell *this)
{
	char	first_char;

	first_char = this->temp[0];
	if (first_char == '\'' || first_char == '\"')
	{
		if (this->temp[1])
			this->temp++;
		while (this->temp[0] && (this->temp[0] != first_char))
			this->temp++;
		if (this->temp[0] == first_char)
			this->temp++;
	}
}

/*
** Counts how many string splinters there'll be.
*/
void	count_words(t_split_shell *this)
{
	this->temp = this->string;
	while (this->temp[0])
	{
		this->words++;
		while (this->temp[0] == this->delimiter)
			this->temp++;
		while (this->temp[0] && (this->temp[0] != this->delimiter))
		{
			if (this->temp[0] == '\'' || this->temp[0] == '\"')
				iterate_through_quotes(this);
			else
				this->temp++;
		}
	}
}