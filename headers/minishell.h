/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 23:09:16 by coder             #+#    #+#             */
/*   Updated: 2022/09/10 23:08:50 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "defs.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h> // sigaction
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
// test_utils.c
int	print_token_list(t_ms_data *ms); // REMOVER ANTES DA ENTREGA
int	check_for_some_shady_shit(t_ms_data *ms); // REMOVER ANTES DA ENTREGA



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
t_tokens	*tokenize_splits(t_ms_data *ms);
void		categorize_tokens(t_tokens *tokens);
int			token_is_error(t_tokens *temp);
int			check_for_non_print(char *value);
// token_types.c
int			token_is_builtin(char *value);
int			token_is_operator(char *value);
int			token_is_redirect(char *value);
int			token_is_word(t_tokens *temp);
int			token_is_command(t_tokens *temp);

/*
** SIGNALS
*/
// signals.c
void		sigint_handler(int signo);
void		sigterm_handler(int signo);
void		sigquit_handler(int signo);

#endif
