/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:38:15 by viferrei          #+#    #+#             */
/*   Updated: 2022/08/28 22:56:23 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Quite literally iterates through the quotes.
*/
static void	iterate_through_quotes(t_split_shell *this)
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
		this->words++;
		return ;
	}
	while (this->temp[0] && (this->temp[0] != this->delimiter))
		this->temp++;
	this->words++;
}

/*
** Counts how many string splinters there'll be.
*/
static void	count_words(t_split_shell *this)
{
	this->temp = this->string;
	while (this->temp[0])
	{
		while (this->temp[0] == this->delimiter)
			this->temp++;
		iterate_through_quotes(this);
	}
}

/*
** Counts how many characaters a given string splinter has.
*/
static int	get_word_size(char *str, char delimiter)
{
	char	*temp;
	char	first_char;
	int		size;

	temp = str;
	size = 0;
	first_char = *temp;
	if (first_char == '\'' || first_char == '\"')
	{
		temp++;
		size++;
		while (*temp && (*temp != first_char))
		{
			temp++;
			size++;
		}
		return (size + (*temp == first_char));
	}
	while (*temp && (*temp != delimiter))
	{
		temp++;
		size++;
	}
	return (size);
}

/*
** Copies while advancing the pointer, in a manner that we don't need to track
** the progress back, while respecting most shell's quotation rules.
*/
static void	copy_to_split(char *split, t_split_shell *this, int i)
{
	char	first_char;

	first_char = this->temp[0];
	if (first_char == '\'' || first_char == '\"')
	{
		split[i++] = first_char;
		this->temp++;
		while (this->temp[0] != first_char)
		{
			split[i] = this->temp[0];
			i++;
			this->temp++;
		}
		this->temp++;
		split[i] = first_char;
		return ;
	}
	while (this->temp[0] && this->temp[0] != ' ')
	{
		split[i] = this->temp[0];
		this->temp++;
		i++;
	}
	split[i] = 0;
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
		splits[this->i] = ft_calloc ((get_word_size
					(this->temp, delimiter) + 1), sizeof(char));
		copy_to_split (splits[this->i], this, 0);
		this->i++;
	}
	this = safe_free(this);
	return (splits);
}
