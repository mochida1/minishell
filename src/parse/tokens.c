/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 02:19:46 by coder             #+#    #+#             */
/*   Updated: 2022/09/10 00:49:40 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** saves tokens into a linked list;
** On success returns an address to the head of the list, else returns NULL.
*/
t_tokens	*tokenize_splits(t_ms_data *ms)
{
	int			i;
	t_tokens	*self;
	t_tokens	*temp;
	t_tokens	*previous;

	if (!ms->rl_split || !ms->rl_split[0])
		return (NULL);
	i = 0;
	self = ft_calloc(1, sizeof(*self));
	temp = self;
	temp->prev = NULL;
	while (ms->rl_split[i])
	{
		temp->value = ft_strdup(ms->rl_split[i]);
		if (ms->rl_split[i + 1])
			temp->next = ft_calloc(1, sizeof(*self));
		previous = temp;
		temp = temp->next;
		if (temp)
			temp->prev = previous;
		i++;
	}
	return (self);
}

/*
** Compares shit with demanded builtin commands.
** Because thinking is for stupid people.
*/
int	token_is_builtin(char *value)
{
	if (!ft_strcmp(value, "echo"))
		return (1);
	if (!ft_strcmp(value, "cd"))
		return (1);
	if (!ft_strcmp(value, "pwd"))
		return (1);
	if (!ft_strcmp(value, "export"))
		return (1);
	if (!ft_strcmp(value, "unset"))
		return (1);
	if (!ft_strcmp(value, "env"))
		return (1);
	if (!ft_strcmp(value, "exit"))
		return (1);
	return (0);
}

/*
** These get operators. If any of those return true, the user has likelly tried
** to fuck you up. Return an error to the MFer.
*/
int	token_is_operator(char *value)
{
	if (!ft_strcmp(value, "|"))
		return (1);
	if (!ft_strcmp(value, "||"))
		return (1);
	if (!ft_strcmp(value, "&"))
		return (1);
	if (!ft_strcmp(value, "&&"))
		return (1);
	if (!ft_strcmp(value, ";"))
		return (1);
	if (!ft_strcmp(value, "\\n"))
		return (1);
	return (0);
}

/*
** If one of those is returned as true, it means that we'll have a lot of
** headache through pipex;
*/
int	token_is_redirect(char *value)
{
	if (!ft_strcmp(value, ">"))
		return (1);
	if (!ft_strcmp(value, ">>"))
		return (1);
	if (!ft_strcmp(value, "<"))
		return (1);
	if (!ft_strcmp(value, "<<"))
		return (1);
	return (0);
}

int	check_for_non_print(char *value)
{
	int	count;

	count = 0;
	while (value[count])
	{
		if(!ft_isprint(value[count]) && (value[count] != 0))
			return (0);
		count++;
	}
	return (1);
}

/*
** This detects if the token is a word;
*/
int	token_is_word(t_tokens *temp)
{
	if (temp->value[0] == '\'' || temp->value[0] == '\"')
		return (1);
	if (temp->prev && temp->prev->type == REDTOKEN)
		return (1);
	if (check_for_non_print(temp->value))
		return (1);
	return (0);
}

/*
** If the word is actaully a command, based on token order, returns 0(COMTOKEN)
** Else returns 2;
*/
int	token_is_command(t_tokens *temp)
{
	if (!temp->prev && !temp->next)
		return (1);
	if (!temp->prev)
		return (1);
	if (temp->prev && temp->prev->type == OPTOKEN)
		return (1);
	if (temp->prev && temp->prev->type == WORDTOKEN)
	{
		if (temp->prev->prev && temp->prev->prev->type == REDTOKEN)
			return(1);
	}
	return (0);
}

/*
** Wrapper to get token types;
*/
int	get_token_type(t_tokens *temp)
{
	int	type_is;

	type_is = ERRTOKEN;
	if (token_is_operator(temp->value))
		return (OPTOKEN);
	if (token_is_redirect(temp->value))
		return (REDTOKEN);
	if (token_is_word(temp))
		type_is = WORDTOKEN;
	if (token_is_command(temp) && type_is == WORDTOKEN)
		type_is = COMTOKEN;
	if (token_is_builtin(temp->value) && type_is == COMTOKEN)
		type_is = BITOKEN;
	return (type_is);
}

/*
** Categorizes token according to their types.
*/
void	categorize_tokens(t_tokens *tokens)
{
	t_tokens *temp;

	temp = tokens;
	while (temp)
	{
		temp->type = get_token_type(temp);
		temp = temp->next;
	}
}
