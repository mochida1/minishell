NAME = minishell
NAME_FS = minishell_fs
MAKEFLAGS = --no-print-directory
BUILDDIR = objs
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
VPATH = src tests src/builtin src/states src/prompt src/utils src/main \
src/exec src/parse src/signals

# headers
INCLUDES = -I /headers

# Lists sources. Manually because of norm...
BUILTIN = builtin_cd_utils.c builtin_cd.c builtin_echo.c builtin_env.c \
			builtin_export.c builtin_pwd.c
EXEC = exec_one_cmd.c handle_redirects.c execve_TESTE.c
MAIN = minishell.c
PARSE = expand_vars_utils.c expand_vars.c token_types.c token_types2.c tokens.c
PROMPT = add_spaces_utils.c add_spaces.c ft_split_shell.c prompt_utils.c
STATES = clean_state.c error_state.c exec_state.c init_state.c parse_state.c \
			prompt_state.c
UTILS = ft_strcmp.c get_env.c safe_free.c test_utils.c
SIGNALS = signals.c
TEST_LIST = test_expand_vars.c

# Names sources
SOURCES = $(BUILTIN) $(EXEC) $(MAIN) $(PARSE) $(PROMPT) $(STATES) $(UTILS) \
			$(SIGNALS) $(TEST_LIST)

# Names objects
OBJS = $(SOURCES:%.c=$(BUILDDIR)/%.o)

# Compiler
CC = gcc
CF = -Wall -Wextra -Werror
GDB = -ggdb
VAL = valgrind --trace-children=yes --leak-check=full --track-origins=yes \
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

$(BUILDDIR)/%.o: %.c $(BUILDDIR)
	@$(CC) $(CF) $(GDB) $(INCLUDES) -c $< -o $@

all: $(NAME)

fs: $(NAME_FS)

test:
	@make -C tests/
	@printf "\n"
	@./tests/tester

clean:
	@rm -rf $(BUILDDIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_FS)
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
