#ifndef MINISHELL_H
# define MINISHELL_H

#include "defs.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include <stdio.h> // readline

// safe_free.c
int			safe_free (void *content);
// add_spaces.c
char		*add_spaces(char *buffer);
//add_spaces_utils.c
int			is_operator(char c);

// get_envs.c
t_env_list	*get_env(char **envp)
void		destroy_env_list(t_env_list *envs)

#endif
