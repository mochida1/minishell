NAME = minishell
NAME_FS = minishell_fs
MAKEFLAGS = --no-print-directory
BUILDDIR = objs
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
VPATH = src tests src/builtin src/states src/prompt src/utils src/main \
src/exec src/parse src/signals src/redirects

# headers
INCLUDES = -I /headers

# Lists sources. Manually because of norm...
BUILTIN = builtin_cd_utils.c builtin_cd.c builtin_echo.c builtin_env.c \
			builtin_export.c builtin_pwd.c builtin_unset.c builtin_exit.c \
			builtin_cd_utils2.c
EXEC = exec_one_cmd.c  exec_com.c exec_multi_cmd.c destroy_exec_info.c \
			get_exec_info.c tok_args.c tok_command.c tok_input.c tok_output.c \
			tok_envp.c tok_utils.c exec_com_utils.c
MAIN = minishell.c
PARSE = expand_exit_code.c expand_vars_utils.c expand_vars.c token_types.c \
			token_types2.c tokens.c parse_check_for_errors.c \
			tokens_remove_quotes.c
PROMPT = add_spaces_utils.c add_spaces.c ft_split_shell.c prompt_utils.c \
			ft_split_shell_utils.c
REDIRECTS = handle_redirects.c heredoc.c heredoc_utils.c redirect_utils.c \
			heredoc_expansions.c
STATES = clean_state.c error_state.c exec_state.c init_state.c parse_state.c \
			prompt_state.c
UTILS	= ft_strcmp.c get_env.c safe_free.c test_utils.c
SIGNALS = signals.c
TEST_LIST = test_expand_vars.c

# Names sources
SOURCES = $(BUILTIN) $(EXEC) $(MAIN) $(PARSE) $(PROMPT) $(REDIRECTS) $(STATES) $(UTILS) \
			$(SIGNALS) $(TEST_LIST)

# Names objects
OBJS = $(addprefix $(BUILDDIR)/, $(SOURCES:%.c=%.o))

# Compiler
CC = clang
CF = -Wall -Wextra -Werror
GDB = -ggdb
VAL = valgrind --trace-children=no --leak-check=full --track-origins=yes \
		./$(NAME)
FSF = -fsanitize=address

$(NAME): $(LIBFT) $(BUILDDIR) $(OBJS)
	@printf "Compiling minishell...\n"
	@$(CC) $(CF) $(OBJS) $(INCLUDES) $(LIBFT) -lreadline -o $(NAME)
	@printf "Done!\n"

$(NAME_FS): $(LIBFT) $(OBJS)
	@$(CC) $(CF) $(FSF) $(OBJS) $(INCLUDES) $(LIBFT) -lreadline -o $(NAME_FS)

$(NAME_TEST): $(LIBFT) $(TEST_OBJS)
	@printf "Compiling test files...\n"
	@$(CC) $(CF) $(TEST_OBJS) $(INCLUDES) $(LIBFT) -o $(NAME_TEST)

$(LIBFT):
	@printf "Compiling libft...\n"
	@make -C $(LIBFT_DIR)

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: %.c
	@$(CC) $(CF) $(GDB) $(INCLUDES) -c $< -o $@

all: $(NAME)

fs: $(NAME_FS)

test:
	@make -C tests/
	@printf "\n"
	@./tests/tester

clean:
	@rm -rf $(BUILDDIR)
	@rm -f vgcore*
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_FS)
	@rm -f vgcore*
	@make fclean -C $(LIBFT_DIR)

re: fclean all

# from here on shit ain't mandatory or bonus
run: all
	$(VAL)

fs: $(NAME_FS)
	./$(NAME_FS)

git: fclean
	git add -A
	git commit -m "make git"
	git push

PHONY:	all clean fclean re run
