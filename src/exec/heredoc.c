/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:03:57 by coder             #+#    #+#             */
/*   Updated: 2022/10/08 01:13:48 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Gera o path de um arquivo randomico para ser utilizado pelo open
*/
static int	generate_a_random_name(char *random_name, char *seed) // ver função heredoc
{
	int	i;
	void	*ptr;

	i = ft_strlcpy(random_name, "/tmp/minishell/", sizeof(random_name));
	i += ft_strlcat(random_name, "msh", sizeof(random_name));
	i += ft_strlcat(random_name, seed, sizeof(random_name));
	ptr = malloc (1);
	if (!ptr)
		return (-1);
	free (ptr)
	ptr = ft_itoa((int) ptr);
	i += ft_strlcat(random_name, ptr, sizeof(random_name));
	free (ptr);
	if (i >= PATH_MAX)
	{
		write (2, "heredoc too big!\n", 17);
		return (-1);
	}
	return (i);
}

/*
** Waits for child to ruin itself while ignore all external signals.
** resumes catching signals after child is killed;
*/
void	daddy_issues(int pid, int i)
{
	if (pid)
	{
		ignore_signals();
		waitpid(pid, &i, 0);
		signal_handlers();
	}
}

static void	print_error(char *target, int line, int ret_fd)
{
	char	*linestr;

	linestr = ft_itoa(line);
	write(2, "bash: warning: here-document at line ", 37);
	write(2, linestr, ft_strlen(linestr));
	write(2, "delimited by end-of-file (wanted '", 34);
	write(2, target, ft_strlen(target));
	write(2, "')\n", 3);
	free (linestr);
	close (ret_fd);
	exit (1);
}

static void	exit_if_eof_sent_by_user(char *buffer, char *target)
{
	if (!ft_strcmp(buffer, target))
	{
		free(buffer);
		exit(0);
	}
}

/*
**	Creates a temporary file,
*/
int	heredoc(char *target)
{
	int		ret_fd;
	int		pid;
	int		i;
	char	*buffer;

	ret_fd = open ("/tmp/minishell/", 0666, O_TMPFILE | O_RDWR);
	pid = fork();
	i = 2;
	daddy_issues(pid, i);
	if (!pid)
	{
		sig_defaults();
		while (1)
		{
			i++;
			buffer = readline(">");
			if (!buffer)
				print_error(target, i, ret_fd);
			exit_if_eof_sent_by_user(buffer, target);
			write(ret_fd, buffer, ft_strlen(buffer));
			write(ret_fd, "\n", 1);
			free(buffer);
		}
	}
	return (ret_fd);
}
