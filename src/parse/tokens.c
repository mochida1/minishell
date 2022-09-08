/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 02:19:46 by coder             #+#    #+#             */
/*   Updated: 2022/09/08 02:38:12 by coder            ###   ########.fr       */
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

	if (!ms->rl_split || !ms->rl_split[0])
		return (NULL);
	i = 0;
	self = ft_calloc(1, sizeof(*self));
	temp = self;
	while (ms->rl_split[i])
	{
		temp->value = ft_strdup(ms->rl_split[i]);
		if (ms->rl_split[i + 1])
			temp->next = ft_calloc(1, sizeof(*self));
		temp = temp->next;
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
	if (!ft_strcmp(value, "|"))
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
** This detects if the
*/
int	token_is_word(char *value)
{
	if (*value == '\'' || *value == '\"')
		return (1);
	if (*value == '-')
		return (1);
	if (check_for_non_print)
		return (1);
}

/*
** Wrapper to get token types;
*/
int	get_token_type(char *value)
{
	if (token_is_builtin(value))
		return (BITOKEN);
	if (token_is_operator(value))
		return (OPTOKEN);
	if (token_is_redirect(value))
		return (REDTOKEN);
	if (token_is_word(value))
		return (WORDTOKEN);
	return (ERRTOKEN);
}

/*
** If the word is actaully a command, based on token order, returns 0(COMTOKEN)
** Else returns 2;
*/
int	check_if_command(t_tokens *temp, t_tokens *tokens)
{
	t_tokens	*retemp;
	int			i;

	i = 0;
	retemp = tokens;
	while (retemp != temp)
	{
		if (retemp->type )
	}

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
		temp->type = get_token_type(temp->value);
		if (temp->type == 2)
			temp->type = check_if_command(temp, tokens);
		temp = temp->next;
	}
}
