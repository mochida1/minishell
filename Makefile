NAME = minishell
NAME_FS = minishell_fs
SOURCEDIR = src
BUILDDIR = objs
LIBS = libs


# Makes make look for source in this dir
#VPATH = $(SOURCEDIR)

# headers
INCLUDES = -I /headers

# Lists sources. Manually because of norm...
SRC_LIST = minishell.c \


# Names sources
SOURCES = $(addprefix $(SOURCEDIR)/,$(SRC_LIST))

# Names objects
OBJS := $(subst $(SOURCEDIR),$(BUILDDIR),$(SOURCES:.c=.o))

# Compiler
CC = gcc
CF = -Wall -Wextra -Werror -lreadline
GDB = -ggdb
VAL = valgrind --trace-children=yes --leak-check=full --track-origins=yes ./$(NAME)
FSF = -fsanitize=address

# Arguments to test the program with
RUN_ARGS = ""

$(NAME): $(OBJS)
	@$(CC) $(CF) $(OBJS) $(INCLUDES) -o $(NAME)

$(NAME_FS): $(OBJS)
	@$(CC) $(CF) $(FSF) $(OBJS) $(INCLUDES) -o $(NAME_FS)

objs/%.o: src/%.c
	@mkdir -p objs
	@$(CC) $(CF) $(GDB) $(INCLUDES) -c $< -o $@

all: $(NAME)

fs: $(NAME_FS)

clean:
	@rm -rf objs

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_FS)

re: fclean all

# maybe if bonus.
bonus:

# from here on shit ain't mandatory or bonus
run: all
	$(VAL) $(RUN_ARGS)

make teste: $(NAME_FS)
	./$(NAME_FS) $(RUN_ARGS)

git: fclean
	git add -A
	git commit -m "make git"
	git push

PHONY:	all clean fclean re run
