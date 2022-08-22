/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 16:49:02 by viferrei          #+#    #+#             */
/*   Updated: 2022/02/21 21:09:09 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>

# define INT_MIN	-2147483648
# define INT_MAX	2147483647
# define UINT_MAX	4294967295
# define OPEN_MAX	256

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);

char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *str, const char *to_find, size_t len);
int			ft_atoi(const char *str);
int			ft_atohex(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);

void		ft_bzero(void *str, size_t n);
void		*ft_memchr(const void *str, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memset(void *str, int c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t len);
void		*ft_memmove(void *dst, const void *src, size_t len);

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
size_t		ft_split_count(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putendl_fd(char *s, int fd);

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ----- GET_NEXT_LINE functions ----- */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

char		*get_next_line(int fd);
int			read_file(int fd, char **buffer, char **s_buff, char **line);
char		*get_line(char **line, char **s_buff);

/* ----- PRINTF structs and functions ----- */

typedef struct s_format
{
	char	*format;
	int		index;
	va_list	arg;
	int		len;
}	t_format;

typedef struct s_holder
{
	char	*argument;
	char	specifier;
	size_t	len;
}	t_holder;

int			ft_printf(const char *format, ...);
int			ft_vprintf(const char *format, va_list arg);

t_format	*ft_init_format(const char *format, va_list arg);
t_holder	*ft_init_holder(void);

void		ft_placeholder(t_format *fmt, t_holder *holder);
void		ft_specifier(t_format *fmt, t_holder *holder);
void		ft_conversions(t_format *fmt, t_holder *holder);

/* CONVERSIONS */
void		ft_convert_c(t_format *fmt, t_holder *holder);
void		ft_convert_di(t_format *fmt, t_holder *holder);
void		ft_convert_u(t_format *fmt, t_holder *holder);
void		ft_convert_s(t_format *fmt, t_holder *holder);
void		ft_convert_percent(t_holder *holder);
void		ft_convert_p(t_format *fmt, t_holder *holder);
void		ft_convert_x(t_format *fmt, t_holder *holder);

/* AUXILIARIES */
char		*ft_uitoa(unsigned int n);
char		*ft_itoa_base(unsigned long nbr, char *base);

#endif
