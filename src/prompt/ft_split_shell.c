/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmochida <hmochida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:38:15 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/15 05:28:09 by hmochida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** counts how many characeters there are till the next quote of the same type
*/
static int	count_till_quo(char *temp)
{
	char	quote;
	int		count;

	count = 0;
	quote = temp[0];
	while (temp[count] && (temp[count] != quote || !count))
	{
		count++;
	}
	if (temp[count] == quote)
	{
		count++;
	}
	return (count);
}

/*
** Counts how many characaters a given string splinter has.
*/
static int	get_word_size(char *str, char delimiter)
{
	char	*temp;
	int		size;
	int		ret;

	temp = str;
	size = 0;
	ret = 0;
	while (*temp && *temp == delimiter)
		temp++;
	while (*temp && *temp != delimiter)
	{
		if (*temp == '\'' || *temp == '\"')
		{
			size = count_till_quo(temp);
			temp += size;
			ret += size;
		}
		else
		{
			temp++;
			ret ++;
		}
	}
	return (ret);
}

/*
** Copies while advancing the pointer, in a manner that we don't need to track
** the progress back, while respecting most shell's quotation rules.
*/
static void	copy_to_split(char *split, t_split_shell *this, int k)
{
	while (k < this->sz)
	{
		split[k] = this->temp[0];
		this->temp++;
		k++;
	}
}

/*
** Splits a string into tokens while obeying shell quotation rules;
** DO NOT USE any type of quotes as the delimiter.
** Caller must dealoc created strings AND pointer;
*/
char	**ft_split_shell(char *str, char delimiter)
{
	char			**splits;
	t_split_shell	*this;

	this = ft_calloc (1, sizeof(*this) + 1);
	this->temp = str;
	this->delimiter = delimiter;
	this->string = str;
	count_words(this);
	splits = ft_calloc ((this->words + 1), sizeof(char *));
	this->temp = this->string;
	while (this->i < this->words)
	{
		while (this->temp[0] == this->delimiter)
			this->temp++;
		this->sz = (get_word_size(this->temp, ' '));
		splits[this->i] = ft_calloc (this->sz + 1, 1);
		copy_to_split (splits[this->i], this, 0);
		this->i++;
	}
	this = safe_free(this);
	return (splits);
}
