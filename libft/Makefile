CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -rf
LIB		= ar -rcs

NAME	= libft.a

INCLUDE	= libft.h
SRC		= ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_tolower.c ft_toupper.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
			ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c \
			ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strdup.c \
			ft_atoi.c ft_atohex.c ft_calloc.c ft_bzero.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
			ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_uitoa.c \
			get_next_line.c \
			ft_printf_convert_cdiusp.c \
			ft_printf_convert_xX_percent.c \
			ft_printf_init_placeholder.c \
			ft_printf.c
BONUS_S	= ft_lstnew.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
			ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c
OBJ_DIR	= ./objs
OBJ		= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
BONUS_O	= $(addprefix $(OBJ_DIR)/, $(BONUS_S:.c=.o))

all: 		$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJ)
			$(LIB) $(NAME) $(OBJ)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o:	%.c	$(INCLUDE)
			$(CC) $(CFLAGS) -c $< -o $@

bonus:		$(BONUS_O)
			$(LIB) $(NAME) $(BONUS_O)

.c.o:		$(INCLUDE)
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
			$(RM) $(OBJ_DIR)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

rebonus:	fclean bonus

.PHONY: 	all clean fclean re bonus rebonus

run:		$(NAME)
			$(RM) a.out
			$(CC) $(CFLAGS)	main.c libft.a && ./a.out
