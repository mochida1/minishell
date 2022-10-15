/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 23:09:13 by coder             #+#    #+#             */
/*   Updated: 2022/10/09 21:22:04 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# ifndef _LINUX_LIMITS_H
#  define _LINUX_LIMITS_H
#  define PATH_MAX		4096
#  define PIPE_BUF		4096
# endif

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
# define FDTOKEN		5

/*
** HEREDOC				<<
** INFILE				<
** OVERWRITE			>
** APPEND				>>
*/
# define NOPE			0
# define HEREDOC		1
# define INFILE			2
# define OVERWRITE		3
# define APPEND			4
# define NO_REDIRECT	-1

typedef struct s_tokens
{
	char			*value;
	int				type;
	int				index;
	struct s_tokens	*next;
	struct s_tokens	*prev;
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
	int					exit_code;
	int					tok_index;
	char				*home_original;
	char				*oldpwd;
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
	int		sz;
}	t_split_shell;

typedef struct s_global
{
	volatile int	exit_code;
}				t_global;

typedef struct s_reds
{
	int				type;
	char			*target;
	struct s_reds	*next;
}				t_reds;

typedef struct s_com
{
	int				block_exec;
	char			*command;
	int				is_builtin;
	char			**args;
	char			**envp;
	struct s_reds	*red_in;
	struct s_reds	*red_out;
	int				receives_from_pipe;
	int				sends_to_pipe;
	char			*error_to_print;
}				t_com;

// GLOBAL VARIABLE
// t_global	g_global;

#endif
