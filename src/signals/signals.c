/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 20:29:26 by coder             #+#    #+#             */
/*   Updated: 2022/09/11 21:09:17 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Handles CTRL+C
*/
void	sigint_handler(int signo)
{
	(void)signo;
	// g_global.exit_code = 130;
	write (1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
** CTRL + raba
*/
void	sigquit_handler(int signo)
{
	(void) signo;
	// g_global.exit_code = 127;
}
