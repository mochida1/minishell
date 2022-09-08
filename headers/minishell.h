/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 23:09:16 by coder             #+#    #+#             */
/*   Updated: 2022/09/08 01:36:08 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "defs.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h> // readline
# include <sys/wait.h> // wait
# include <assert.h> /* assert serve como um 'if (false){quebra o programa}'*/

// STATES
int			error_state(t_ms_data *ms);
int			init_state(t_ms_data *ms, int argc, char *argv[], char **envp);
int			prompt_state(t_ms_data *ms);
int			parse_state(t_ms_data *ms);
int			exec_state(t_ms_data *ms, char **envp);
int			clean_state(t_ms_data *ms);


/*
** UTILS
*/
// safe_free.c
void		*safe_free(void *content);
void		*free_rl_split(t_ms_data *ms);
void		*destroy_token_list(t_ms_data *ms);

// ft_strcmp.c
int			ft_strcmp (char *str, char *str2);

// get_envs.c
t_env_list	*get_env(char **envp);
void		*destroy_env_list(t_env_list *envs);

/*
** PROMPT
*/
// add_spaces.c
char		*add_spaces(char *buffer, t_ms_data *ms);

// add_spaces_utils.c
int			is_operator(char c);

// prompt_utils.c
int			set_prompt(t_ms_data *ms);
int			get_data_from_readline(t_ms_data *ms);

// ft_split_shell.c
char	**ft_split_shell(char *str, char delimiter);

// execve_TESTE.c
int			exec_MVP_TESTE(t_ms_data *ms, char **envp);

/*
** PARSE
*/
// tokens.c
void		categorize_tokens(t_tokens *tokens);

#endif
