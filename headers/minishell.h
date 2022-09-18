/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 23:09:16 by coder             #+#    #+#             */
/*   Updated: 2022/09/18 20:16:11 by viferrei         ###   ########.fr       */
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

/*
** BUILTIN 
*/
int			env(t_env_list	*env_list);

/*
** EXEC
*/
// exec_one_cmd.c
int			has_pipe(t_tokens *tokens);
void		exec_one_cmd(t_ms_data *ms);

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

// builtin_cd_utils.c
int			count_args(char **args);
char		*get_home_dir_from_envs(t_ms_data *ms);

// ft_strcmp.c
int			ft_strcmp(char *str, char *str2);

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
char		**ft_split_shell(char *str, char delimiter);

// execve_TESTE.c
int			exec_MVP_TESTE(t_ms_data *ms, char **envp);

/*
** PARSE
*/
// expand_vars_utils.c
int			is_variable(char c);
char		*find_variable(char	*str);

// expand_vars.c
int			expand_variables(t_ms_data *ms);

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

/*
** BUILTINS
*/
// builtin_pwd.c
int			builtin_pwd(char **args, t_ms_data *ms);

// builtin_cd.c
int			builtin_cd(char **args, t_ms_data *ms);
// builtin_cd_utils.c
char		*expand_home(char *path, t_ms_data *ms);
int			count_args(char **args);
char		*get_home_dir_from_envs(t_ms_data *ms);

/*
** TESTS
*/
void		test_expand_vars(t_ms_data *ms); // REMOVER ANTES DA ENTREGA

#endif
