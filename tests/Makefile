NAME = tester
NAME_FS = tester_fs
MAKEFLAGS = --no-print-directory
SRCDIR = ../src
BUILDDIR = test_objs
TESTDIR = ./
LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a
VPATH = ../ src tests
INCLUDE = -I ../

# headers
INCLUDES = -I /headers

# WITHOUT MINISHELL.C BECAUSE OF MAIN
SRC_LIST = add_spaces_utils.c add_spaces.c safe_free.c split_cmds.c
TEST_LIST = main_tests.c

# Names sources
SOURCES = $(SRC_LIST)

# Names objects
OBJS = $(SOURCES:%.c=$(BUILDDIR)/%.o)
TEST_OBJS = $(TEST_LIST:%.c=%.o) 

# Compiler
CC = gcc
CF = -Wall -Wextra -Werror
GDB = -ggdb
VAL = valgrind --trace-children=yes --leak-check=full --track-origins=yes \
		./$(NAME)
FSF = -fsanitize=address

$(NAME): $(LIBFT) $(BUILDDIR) $(OBJS) $(TEST_OBJS)
	@printf "Compiling tester...\n"
	$(CC) $(CF) $(OBJS) $(BUILDDIR)/$(TEST_OBJS) $(INCLUDES) $(LIBFT) -o $(NAME)
	@printf "Done!\n"

$(NAME_FS): $(LIBFT) $(OBJS)
	@$(CC) $(CF) $(FSF) $(OBJS) $(INCLUDES) $(LIBFT) -o $(NAME_FS)

$(LIBFT):
	@printf "Compiling libft...\n"
	@make -C $(LIBFT_DIR)

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CF) $(GDB) $(INCLUDES) -c $< -o $@

# Creates object files in present directory
%.o: %.c
	@$(CC) $(CF) $(GDB) $(INCLUDES) -c $< -o $@
	@mv *.o $(BUILDDIR)/

all: $(NAME)

fs: $(NAME_FS)

test: $(NAME_TEST)

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
	$(VAL) $(RUN_ARGS)

fs: $(NAME_FS)
	./$(NAME_FS)

git: fclean
	git add -A
	git commit -m "make git"
	git push

PHONY:	all clean fclean re run
