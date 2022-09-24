/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:12:17 by viferrei          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/22 02:01:11 by coder            ###   ########.fr       */
=======
/*   Updated: 2022/09/23 00:14:10 by viferrei         ###   ########.fr       */
>>>>>>> 565e31fe1e8a3cc1a476b37884d04c1a6a5b5e03
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	export(t_ms_data *ms)
{
	t_env_list	*head;
<<<<<<< HEAD
=======
	// (void) args;
>>>>>>> 565e31fe1e8a3cc1a476b37884d04c1a6a5b5e03

	head = ms->env_head;
	while (head->next)
		head = head->next;
	head->next = ft_calloc(1, sizeof(t_env_list));
	head = head->next;
	// head->content =
	return(0);
}
