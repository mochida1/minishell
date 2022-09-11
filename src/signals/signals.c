/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 20:29:26 by coder             #+#    #+#             */
/*   Updated: 2022/09/10 23:16:48 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Handles CTRL+C
*/
void	sigint_handler(int signo)
{
	printf ("%d MANDEI CTRL+C!\n", signo);
}

/*
** Handles CTRL+D
*/
void	sigterm_handler(int signo)
{
	printf ("%d, MANDEI CTRL+D!\n", signo);
}

/*
** CTRL + raba
*/
void	sigquit_handler(int signo)
{
	printf ("%d MANDEI CTRL+RABA!\n", signo);
}
