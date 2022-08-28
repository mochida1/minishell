/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 23:09:13 by coder             #+#    #+#             */
/*   Updated: 2022/08/28 02:52:22 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

typedef struct s_env_list
{
	char				*content;
	struct s_env_list	*next;
}				t_env_list;

typedef struct s_ms_data
{
	int	state;
	char	*rl_buffer;
	char	*rl_prompt;
	struct s_env_list *env_head;

}				t_ms_data;

#endif
