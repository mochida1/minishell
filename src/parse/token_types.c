/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 16:44:54 by coder             #+#    #+#             */
/*   Updated: 2022/09/11 01:15:35 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
			return (1);
	}
	return (0);
}
