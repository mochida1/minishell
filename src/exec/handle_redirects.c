/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:48:16 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/05 02:26:39 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// Handle redirects for one command only.
void	handle_redirects(t_com *cmd)
{
	t_reds	*infile;
	t_reds	*outfile;

	infile = cmd->red_in;
	outfile = cmd->red_out;
	while (infile->next)
		infile = infile->next;
	while (outfile->next)
		outfile = outfile->next;
	if (infile->target && access(infile->target, F_OK))
		printf("%s: No such file or directory\n", infile->target);
	else if (infile->target)
		dup2(open(infile->target, O_RDONLY), STDIN_FILENO);
	if (outfile)
		dup2(open(outfile->target, O_CREAT | O_WRONLY | O_TRUNC, 0777), \
					STDOUT_FILENO);
}
