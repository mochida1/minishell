/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:18:04 by coder             #+#    #+#             */
/*   Updated: 2022/08/28 23:07:18 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** wrapper for the given state
*/
int	error_state(t_ms_data *ms)
{
	destroy_env_list(ms->env_head);
	exit(ms->state * -1);
}
