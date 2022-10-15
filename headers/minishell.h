/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmochida <hmochida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:46:15 by viferrei          #+#    #+#             */
/*   Updated: 2022/10/14 20:16:05 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "defs.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h> // open
# include <signal.h> // sigaction
# include <stdio.h> // readline
# include <sys/wait.h> // wait
# include <sys/stat.h> // stat

/*
** BUILTIN
*/
int			builtin_env(char **args, char **envp, t_env_list *env_list);
int			builtin_export(char	**args, t_ms_data *ms);
int			builtin_echo(char **args);
int			builtin_unset(char	**args, t_ms_data *ms);
int			builtin_exit(t_com *cmd, char **args, char **envp, t_ms_data *ms);
// builtin_pwd.c
int			builtin_pwd(char **args, char **envp, t_ms_data *ms);
// builtin_cd.c
int			builtin_cd(char **args, char **envp, t_ms_data *ms);
// builtin_cd_utils.c
char		*expand_home(char *path, t_ms_data *ms);
int			count_args(char **args);
char		*get_home_dir_from_envs(t_ms_data *ms);
int			cd_error_args(t_ms_data *ms);
// builtin_cd_utils2.c
int			update_pwd(t_ms_data *ms, char *path);
int			update_oldpwd(t_ms_data *ms, char *curr_path);

/*
** EXEC
*/
// exec_one_cmd.c
int			has_pipe(t_tokens *tokens);
int			exec_builtin(t_com *cmd, t_ms_data *ms);
int			exec_one_cmd(t_com *cmd, t_ms_data *ms, int original_fds[2]);
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
// exec_com.c
int			exec_fork_builtin(t_com *cmd, t_ms_data *ms);
int			exec_com(t_com *cmd, t_ms_data *ms);
//
int			exec_multi(t_com *cmd, t_ms_data *ms, int original_fds[2]);
// exec_com_utils.c
int			get_exec_error(char *path, t_ms_data *ms);
char		*get_path(char *cmd_arg, char **envp);

// STATES
int			error_state(t_ms_data *ms);
int			init_state(t_ms_data *ms, int argc, char *argv[], char **envp);
int			prompt_state(t_ms_data *ms);
int			parse_state(t_ms_data *ms);
int			exec_state(t_ms_data *ms);
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
void		count_words(t_split_shell *this);

/*
** REDIRECTS
*/
// handle_redirects.c
int			handle_redirects(t_com *cmd, int original_fds[2], t_ms_data *ms);
int			restore_original_fds(int original_fds[2]);

// heredoc.c, heredoc_utils.c
char		*heredoc(char *target, t_ms_data *ms);
int			write_to_heredoc(int ret_fd, char *target);

// redirect_utils.c
int			restore_input(int original_fds[2]);
int			restore_original_fds(int original_fds[2]);

/*
** PARSE
*/
// expand_vars_utils.c
int			vars_match(char *env_var, char *var_name);
char		*get_var_name(char	*var_head);
int			is_variable(char c);
char		*find_variable(char	*str);

// expand_vars.c
void		handle_variable_expansions(t_ms_data *ms);
void		expand_exit_code(t_ms_data *ms);
void		expand_variables(t_ms_data *ms);

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

// tokens_remove_quotes.c
void		remove_quotes_from_tokens(t_tokens *tokens);

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

#endif
