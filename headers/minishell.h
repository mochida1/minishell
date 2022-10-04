/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 23:09:16 by coder             #+#    #+#             */
/*   Updated: 2022/10/05 01:27:13 by coder            ###   ########.fr       */
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
int			builtin_env(char **args, char **envp, t_env_list *env_list);
int			builtin_export(char	**args, t_ms_data *ms);
int			builtin_echo(char **args);
int			builtin_unset(char	**args, t_ms_data *ms);
int			builtin_exit(char **args, char **envp, t_ms_data *ms);
// builtin_pwd.c
int			builtin_pwd(char **args, char **envp, t_ms_data *ms);
// builtin_cd.c
int			builtin_cd(char **args, char **envp, t_ms_data *ms);
// builtin_cd_utils.c
char		*expand_home(char *path, t_ms_data *ms);
int			count_args(char **args);
char		*get_home_dir_from_envs(t_ms_data *ms);

/*
** EXEC
*/
// exec_one_cmd.c
int			has_pipe(t_tokens *tokens);
int			exec_one_cmd(t_com *cmd, t_ms_data *ms);

// handle_redirects.c
void		handle_redirects(t_ms_data *ms);
// get_exec_info.c
t_com		*get_exec_info(t_ms_data *ms);

// destroy_exec_info.c
void		*destroy_exec_info(t_com *self);

// tok_command.c
char		*tok_command(t_ms_data *ms, t_com *self);

// tok_args.c
char		**tok_args(t_ms_data *ms);

// tok_input.c
t_reds		*tok_input(t_ms_data *ms);

// tok_output.c
t_reds		*tok_output(t_ms_data *ms);

// tok_envp.c
char		**tok_envp(t_env_list *head);

// tok_utils.c
t_tokens	*iterate_to_tok_index(t_ms_data *ms);
t_reds		*create_red_list(int nodes);

// STATES
int			error_state(t_ms_data *ms);
int			init_state(t_ms_data *ms, int argc, char *argv[], char **envp);
int			prompt_state(t_ms_data *ms);
int			parse_state(t_ms_data *ms);
int			exec_state(t_ms_data *ms/*, char **envp*/);
int			clean_state(t_ms_data *ms);

/*
** UTILS
*/
// safe_free.c
void		*safe_free(void *content);
void		*free_rl_split(t_ms_data *ms);
void		*destroy_token_list(t_ms_data *ms);
void		*free_pp_char(char **pp);

// ft_strcmp.c
int			ft_strcmp(char *str, char *str2);

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
char		**ft_split_shell(char *str, char delimiter);


/*
** PARSE
*/
// expand_vars_utils.c
int			vars_match(char *env_var, char *var_name);
char		*get_var_name(char	*var_head);
int			is_variable(char c);
char		*find_variable(char	*str);

// expand_vars.c
int			expand_variables(t_ms_data *ms);

// parse_check_for_errors.c
int			parse_check_for_errors(t_ms_data *ms);

// tokens.c
t_tokens	*tokenize_splits(t_ms_data *ms);
void		categorize_tokens(t_tokens *tokens);
int			check_for_non_print(char *value);

// token_types.c
int			token_is_builtin(char *value);
int			token_is_operator(char *value);
int			token_is_redirect(char *value);
int			token_is_word(t_tokens *temp);
int			token_is_command(t_tokens *temp);

// token_types_2.c
int			token_is_error(t_tokens *temp);
int			token_is_fd(t_tokens *temp);

/*
** SIGNALS
*/
// signals.c
int			signal_handlers(void);
void		sigint_handler(int signo);
void		sig_defaults(void);
void		ignore_signals(void);

/*
** TESTS
*/
void		test_expand_vars(t_ms_data *ms); // REMOVER ANTES DA ENTREGA
// test_utils.c
int			print_token_list(t_ms_data *ms); // REMOVER ANTES DA ENTREGA
int			check_for_some_shady_shit(t_ms_data *ms); // REMOVER ANTES DA ENTREGA
void		PRINT_COM(t_com *data); // REMOVER ANTES DA ENTREGA
// execve_TESTE.c
int			exec_MVP_TESTE(t_com *cmd, t_ms_data *ms); // REMOVER ANTES DA ENTREGA

#endif
