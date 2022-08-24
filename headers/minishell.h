#ifndef MINISHELL_H
# define MINISHELL_H

#include "defs.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include <stdio.h> // readline

int		safe_free (void *content);
int		is_operator(char c);
char	*add_spaces(char *buffer);

#endif
