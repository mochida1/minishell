/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:41:10 by coder             #+#    #+#             */
/*   Updated: 2022/10/16 19:13:55 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	print_error(char *target, int line, int ret_fd)
{
	char	*linestr;

	linestr = ft_itoa(line);
	write(2, "bash: warning: here-document at line ", 37);
	write(2, linestr, ft_strlen(linestr));
	write(2, " delimited by end-of-file (wanted '", 35);
	write(2, target, ft_strlen(target));
	write(2, "')\n", 3);
	free (linestr);
	close (ret_fd);
}

int	write_to_heredoc(int ret_fd, char *target, t_ms_data *ms)
{
	int		i;
	char	*buffer;

	i = 2;
	while (1)
	{
		i++;
		buffer = readline(">");
		if (!buffer)
		{
			print_error(target, i, ret_fd);
			return (1);
		}
		buffer = heredoc_handle_expansions(buffer, ms);
		if (!ft_strcmp(buffer, target))
		{
			free(buffer);
			return (1);
		}
		write(ret_fd, buffer, ft_strlen(buffer));
		write(ret_fd, "\n", 1);
		free(buffer);
	}
	return (0);
}
