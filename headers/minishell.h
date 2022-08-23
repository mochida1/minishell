#ifndef MINISHELL_H
# define MINISHELL_H
#include "defs.h"
#include "add_spaces.h"
#include "../libft/libft.h"
#include <stdio.h> // readline

//	add_spaces_utils.c
int		is_operator(char c);
char	*add_spaces(char *buffer);

#endif
