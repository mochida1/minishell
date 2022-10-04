/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:48:16 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/05 01:36:57 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Handle redirects for one command only.
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
		if (!ft_strcmp(tokens->value, "<"))
			infile = tokens->next->value;
		if (!ft_strcmp(tokens->value, ">"))
			outfile = tokens->next->value;
		tokens = tokens->next;
	}
	if (infile && access(infile, F_OK))
		printf("%s: No such file or directory\n", infile);
	else if (infile)
		dup2(open(infile, O_RDONLY), STDIN_FILENO);
	if (outfile)
		dup2(open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0777), STDOUT_FILENO);
}
