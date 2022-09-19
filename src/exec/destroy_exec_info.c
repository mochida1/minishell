/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_exec_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 01:03:03 by coder             #+#    #+#             */
/*   Updated: 2022/09/19 01:03:15 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** Use to free all stuff inside the given t_com struct.
** ie: self = destroy_exec_info(self);
*/
void	*destroy_exec_info(t_com *self)
{
	if (!self)
		return (NULL);
}
