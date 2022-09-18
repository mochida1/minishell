/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:48:16 by viferrei          #+#    #+#             */
/*   Updated: 2022/09/18 22:21:40 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_redirects(t_ms_data *ms)
{
	t_tokens	*tokens;
	char		*infile;
	char		*outfile;

	tokens = ms->tokens;
	infile = NULL;
	outfile = NULL;
	while (tokens)
	{
		if (tokens == '<')
			infile = tokens->next->value;
		if (tokens == '>')
			outfile = tokens->next->value;
		tokens = tokens->next;
	}
	if (access(infile, F_OK))
		printf("%s: No such file or directory\n", infile);
	else
		dup2(open(infile, O_RDONLY), STDIN_FILENO);
	if (outfile)
		dup2(open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0777), STDOUT_FILENO);
}