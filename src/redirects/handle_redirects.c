/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:48:16 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/08 03:14:37 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	redirect_input(t_reds *in)
{
	int	fd;

	if (in->target && access(in->target, F_OK))
	{
		printf("%s: No such file or directory\n", in->target);
		return (1);
	}
	else if (in->target)
	{
		fd = open(in->target, O_RDONLY, FD_CLOEXEC);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	redirect_heredoc(int original_fds[2], t_reds *in, t_ms_data *ms)
{
	char	*heredoc_file;
	int		fd;

	restore_input(original_fds);
	heredoc_file = heredoc(in->target, ms);
	if (!heredoc_file)
		return (1);
	fd = open(heredoc_file, O_RDONLY, FD_CLOEXEC);
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(heredoc_file);
	free(heredoc_file);
	return (0);
}

int	handle_input(t_reds *red_in, int original_fds[2], t_ms_data *ms)
{
	t_reds	*in;

	in = red_in;
	if (!in)
		return (0);
	if (original_fds[0] == NO_REDIRECT)
		original_fds[0] = dup(STDIN_FILENO);
	while (in)
	{
		if (in->type == INFILE)
			if (redirect_input(in))
				return (1);
		if (in->type == HEREDOC)
			if (redirect_heredoc(original_fds, in, ms))
				return (1);
		in = in->next;
	}
	return (0);
}

int	handle_output(t_reds *red_out, int original_fds[2])
{
	t_reds	*out;
	int		fd;

	out = red_out;
	if (!out)
		return (0);
	if (original_fds[1] == NO_REDIRECT)
		original_fds[1] = dup(STDOUT_FILENO);
	while (out)
	{
		if (out->type == OVERWRITE)
			fd = open(out->target, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		else if (out->type == APPEND)
			fd = open(out->target, O_CREAT | O_WRONLY | O_APPEND, 0777);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		out = out->next;
	}
	return (0);
}

// Handle redirects for one command only.
int	handle_redirects(t_com *cmd, int original_fds[2], t_ms_data *ms)
{
	if (handle_input(cmd->red_in, original_fds, ms))
		return (1);
	handle_output(cmd->red_out, original_fds);
	return (0);
}
