/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:30:49 by coder             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/24 02:55:23 by coder            ###   ########.fr       */
=======
/*   Updated: 2022/08/27 01:06:43 by coder            ###   ########.fr       */
>>>>>>> hm-add_spaces
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/*
** Checks if the characater BEFORE op_index should be a [space];
*/
int	need_space_before(char *buffer, int op_index, char operator)
{
	int	flag;

	flag = 0;
	if (op_index == 0)
		return (0);
	op_index--;
	while (op_index)
	{
		if (buffer[op_index] == operator)
		{
			if (flag)
				return (1);
			flag++;
		}
		if (flag && buffer[op_index - 1] != operator)
			return (0);
		else if (buffer[op_index] != ' ')
			return (1);
		else if (buffer[op_index] == ' ')
			return (0);
		op_index--;
	}
	return (0);
}

/*
** Checks if the characater AFTER op_index should be a [space];
*/
int	need_space_after(char *buffer, int op_index, char operator)
{
	int	flag;

	flag = 0;
	op_index++;
	while (op_index)
	{
		if (buffer[op_index] == operator)
		{
			if (flag == 2)
				return (1);
			flag++;
		}
		if (flag && buffer[op_index + 1] != operator)
			return (0);
		else if (buffer[op_index] != ' ' && buffer[op_index] != 0)
			return (1);
		else if (buffer[op_index] == ' ' || buffer[op_index] == 0)
			return (0);
		op_index++;
	}
	return (0);
}

/*
** Creates a new string, adding [space] after given index;
*/
char	*add_space_before_index(char *buffer, int index)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = malloc (sizeof (char) * (ft_strlen(buffer) + 2));
	while (buffer[i])
	{
		if (i == index)
		{
			ret[j] = ' ';
			j++;
		}
		ret[j] = buffer[i];
		i++;
		j++;
	}
	ret[j] = 0;
	return (ret);
}

char	*recursively_does_some_black_magic(char *buffer, int i)
{
	char	*temp;

	if (need_space_before(buffer, i, buffer[i]))
	{
		temp = add_space_before_index(buffer, i);
		safe_free(buffer);
		buffer = temp;
		temp = NULL;
		return (add_spaces(buffer));
	}
	if (need_space_after(buffer, i, buffer[i]))
	{
		temp = add_space_before_index(buffer, i + 1);
		safe_free(buffer);
		buffer = temp;
		temp = NULL;
		return (add_spaces(buffer));
	}
	return (buffer);
}

/*
** Creates an allocated string, inserting spaces if before or after '<', '>',
** '<<', '>>' ou '|', there are no spaces; Does not deals with ||. It spaces it;
*/
char	*add_spaces(char *buffer)
{
	int		i;
	char	*temp;
	int		sin_quote;
	int		dou_quote;

	i = 0;
	temp = NULL;
	sin_quote = 0;
	dou_quote = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\'' && (dou_quote % 2 == 0))
			sin_quote++;
		if (buffer[i] == '\"' && (sin_quote % 2 == 0))
			dou_quote++;
		if ((dou_quote % 2) || (sin_quote % 2))
		{
			i++;
			continue ;
		}
		if (is_operator(buffer[i]))
			buffer = recursively_does_some_black_magic(buffer, i);
		i++;
	}
	return (buffer);
}
