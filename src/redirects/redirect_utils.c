/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 03:52:44 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/09 03:53:04 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	restore_input(int original_fds[2])
{
	if (original_fds[0] != NO_REDIRECT)
		dup2(original_fds[0], STDIN_FILENO);
	return (0);
}

int	restore_original_fds(int original_fds[2])
{
	restore_input(original_fds);
	if (original_fds[1] != NO_REDIRECT)
		dup2(original_fds[1], STDOUT_FILENO);
	return (0);
}
