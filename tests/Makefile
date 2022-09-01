NAME = tester
MAKEFLAGS = --no-print-directory
VFLAGS = --trace-children=yes --leak-check=full --track-origins=yes

# DIRECTORIES
SRCDIR = ../
BUILDDIR = objs_test
LIBFT_DIR = ../libft

LIBFT = $(LIBFT_DIR)/libft.a
VPATH = ../src ../src/builtin ../src/states ../src/prompt ../src/utils
INCLUDE = -I ../

SOURCES = expand_vars.c \
			main_tests.c 
OBJS = $(SOURCES:%.c=$(BUILDDIR)/%.o)

# COMPILER
CC = gcc
CF = -Wall -Wextra -Werror
GDB = -ggdb
VAL = valgrind --trace-children=yes --leak-check=full --track-origins=yes \
		./$(NAME)

# Color codes (ANSI escape codes)
GREEN=\033[1;32m
NC=\033[0m # No Color

# EXECUTABLE
$(NAME): $(LIBFT) $(BUILDDIR) $(OBJS)
	@printf "\n$(GREEN)Compiling tester...$(NC)\n"
	$(CC) $(CF) $(OBJS) $(INCLUDES) $(LIBFT) -o $(NAME)
	@printf "\n$(GREEN)Done!$(NC)\n\n"

# OBJECT FILES
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)
	@printf "\n$(GREEN)Compiling object files...$(NC)\n"

$(BUILDDIR)/%.o: $(SRCDIR)/*/*/%.c	# looks for all .c files in root directory
	$(CC) $(CF) $(GDB) $(INCLUDES) -c $< -o $@

# LIBFT
$(LIBFT):
	@printf "$(GREEN)Compiling libft...$(NC)\n"
	@make -C $(LIBFT_DIR)

all: $(NAME)

clean:
	@rm -rf $(BUILDDIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_FS)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

# from here on shit ain't mandatory or bonus
val:
	valgrind $(VFLAGS) ./$(NAME)

git: fclean
	git add -A
	git commit -m "make git"
	git push

PHONY: all clean fclean re run

meme:
	@printf "                             ▄██▄\n"
	@printf "                             ▀███\n"
	@printf "                                █\n"
	@printf "               \e[0;93m▄▄▄▄▄\e[0m            █\n"
	@printf "              \e[0;93m▀▄    ▀▄\e[0m          █\n"
	@printf "          ▄▀▀▀▄ \e[0;93m█\e[0m▄▄▄▄\e[0;93m█\e[0m▄▄ ▄▀▀▀▄  █      \e[1;95;7mCOMPILE\e[0m\n"
	@printf "         █  ▄  █        █   ▄ █ █      \e[1;92;7m  ALL  \e[0m\n"
	@printf "         ▀▄   ▄▀        ▀▄   ▄▀ █      \e[1;95;7m  THE  \e[0m\n"
	@printf "          █▀▀▀            ▀▀▀ █ █      \e[1;95;7mTHINGS!\e[0m\n"
	@printf "          █                   █ █\n"
	@printf "▄▀▄▄▀▄    █  ▄█▀█▀█▀█▀█▀█▄    █ █\n"
	@printf "█▒▒▒▒█    █  █████████████▄   █ █\n"
	@printf "█▒▒▒▒█    █  ██████████████▄  █ █\n"
	@printf "█▒▒▒▒█    █   ██████████████▄ █ █\n"
	@printf "█▒▒▒▒█    █    ██████████████ █ █\n"
	@printf "█▒▒▒▒█    █   ██████████████▀ █ █\n"
	@printf "█▒▒▒▒█   ██   ██████████████  █ █\n"
	@printf "▀████▀  ██▀█  █████████████▀  █▄█\n"
	@printf "  ██   ██  ▀█  █▄█▄█▄█▄█▄█▀  ▄█▀\n"
	@printf "  ██  ██    ▀█             ▄▀\e[0;95m▓\e[0m█\n"
	@printf "  ██ ██      ▀█▀▄▄▄▄▄▄▄▄▄▀▀\e[0;95m▓▓▓\e[0m█\n"
	@printf "  ████        █\e[0;95m▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\e[0m█\n"
	@printf "  ███         █\e[0;95m▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\e[0m█\n"
	@printf "  ██          █\e[0;95m▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\e[0m█\n"
	@printf "  ██          █\e[0;95m▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\e[0m█\n"
	@printf "  ██         ▐█\e[0;95m▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\e[0m█\n"
	@printf "  ██        ▐█\e[0;95m▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\e[0m█\n"
	@printf "  ██       ▐█\e[0;95m▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\e[0m█▌\n"
	@printf "  ██      ▐█\e[0;95m▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\e[0m█▌\n"
	@printf "  ██     ▐█\e[0;95m▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\e[0m█▌\n"
	@printf "  ██    ▐█\e[0;95m▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\e[0m█▌\n"