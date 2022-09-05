/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 23:09:13 by coder             #+#    #+#             */
/*   Updated: 2022/09/05 21:17:32 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

/*
** STATE definitions
*/
# define ERRSTATE		0
# define INITSTATE		1
# define PROMPTSTATE	2
# define PARSESTATE		3
# define EXECSTATE		4
# define CLEANSTATE		5

/*
** TOKEN TYPE definitions
** ERRTOKEN:	token should return error if used, or is of unknown type;
** COMTOKEN:	categorizes a word to be a COMMAND;
** BITOKEN:		token is a BUILT IN COMMAND;
** WORDTOKEN:	symbolizes a WORD to be used as ARGUMENT after the command;
** OPTOKEN:		indicates that element is a CONTROL OPERATOR;
** REDTOKEN:	token is a FD REDIRECTION OPERATOR;
*/
# define ERRTOKEN		-1
# define COMTOKEN		0
# define BITOKEN		1
# define WORDTOKEN		2
# define OPTOKEN		3
# define REDTOKEN		4

typedef struct s_tokens
{
	char			*value;
	int				type;
	struct s_tokens	*next;
}				t_tokens;

typedef struct s_env_list
{
	char				*content;
	struct s_env_list	*next;
}				t_env_list;

typedef struct s_ms_data
{
	int					set_buffer_to_null;
	int					state;
	int					issue_exit;
	char				*rl_buffer;
	char				*rl_spaced_buffer;
	char				*rl_prompt;
	char				**rl_split;
	struct s_env_list	*env_head;
	struct s_tokens		*tokens;
}				t_ms_data;

typedef struct s_split_shell
{
	char	*string;
	char	*temp;
	int		words;
	int		i;
	int		split_number;
	char	delimiter;
}	t_split_shell;

#endif
