/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:12:58 by coder             #+#    #+#             */
/*   Updated: 2022/09/23 00:30:47 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


/*
** THIS IS A DEBUGGING FUNCTION
** Printa uma struct de comandos.
*/
void	PRINT_COM(t_com *data)
{
	int i = 0;
	printf ("command: %s\n", data->command);
	printf ("error: %s\n", data->error_to_print);
	while (data->args && data->args[i])
	{
		printf ("arg[%d]: %s\n", i, data->args[i]);
		i++;
	}
	i = 0;
	while (data->envp[i])
	{
		printf ("envp[%d]: %s\n", i, data->envp[i]);
		i++;
	}
	t_reds	*temp = data->red_in;
	while (temp)
	{
		printf ("in:%d, %s\n", temp->type, temp->target);
		temp = temp->next;
	}
	temp = data->red_out;
	while (temp)
	{
		printf ("out:%d, %s\n", temp->type, temp->target);
		temp = temp->next;
	}
}

/*
** THIS IS A DEBUGGING FUNCTION
** prints the tokens. Yup. With printf.
*/
int	print_token_list(t_ms_data *ms)
{
	int	ret;
	t_tokens *temp;

	ret = 0;
	temp = ms->tokens;
	while (temp)
	{
		printf ("<: %p\n", temp->prev);
		printf ("v: %p\n", temp);
		printf (">: %p\n", temp->next);
		ret += printf ("v: %s\n", temp->value);
		printf ("t: %d\n", temp->type);
		printf ("\n------------------\n");
		temp = temp->next;
	}
	// printf ("total printed: %d\n", ret);
	// sleep(5);
	return (ret);
}

/*
** THIS IS A DEBUGGING FUNCTION
** sets state to state to -1 and returns the number of fucked up shit you've got
** if all goes well, it'll continue to execute
*/
int	check_for_some_shady_shit(t_ms_data *ms)
{
	int	shaddy_shit_has_happened;

	shaddy_shit_has_happened = 0;
	if (!ms->tokens)
	{
		ms->state = -1;
		shaddy_shit_has_happened++;
	}
	if (!ms->rl_prompt)
	{
		ms->state = -1;
		shaddy_shit_has_happened++;
	}
	if (!ms->env_head)
	{
		ms->state = -1;
		shaddy_shit_has_happened++;
	}
	return (shaddy_shit_has_happened);
}
