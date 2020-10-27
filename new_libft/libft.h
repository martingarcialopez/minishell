/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:13:42 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/10 18:47:14 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>

# define FLAG_MIN 1u
# define FLAG_ZERO 2u
# define FLAG_DOT 4u
# define FLAG_STAR 8u

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_statlst
{
	int					fd;
	char				*content;
	struct s_statlst	*next;
}				t_statlst;

typedef struct	s_form
{
	unsigned int	flag;
	int				prec;
	int				just;
	char			type;
}				t_form;

void			*ft_memset(void *b, int c, size_t len);
size_t			ft_strlen(const char *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
long			ft_atoi(const char *str);
int				ft_isdigit(int c);
int				ft_isspace(char c);
char			*ft_strnstr(const char *haystack, const char *needle, size_t n);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_isinstr(char c, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
int				ft_countstrings(char const *s, char c);
int				ft_doingmalloc(char **split, char const *s, char c);
char			**ft_split(char const *s, char c);
int				ft_lengthnumb(int n);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_fillstr(char **split, char const *s, char c);
void			ft_doingfree(char **split, int count);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
				void (*del)(void *));
int				gnl(int fd, char **line);
char			*ft_ovread(char **line, char *content);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *s);
void			ft_freelst(int fd, t_statlst **lst);
int				ft_isnotthetype(char c);
int				ft_isnothing(char c);
void			ft_doingjust(int just, char c);
int				ft_printchar(t_form *info, va_list args);
int				ft_printstring(t_form *info, va_list args);
int				ft_printperc(t_form *info);
int				ft_printint(t_form *info, va_list args);
int				ft_printuint(t_form *info, va_list args);
int				ft_printhex(t_form *info, va_list args);
int				ft_printf(const char *format, ...);
void			ft_suport(int *i, const char **format);
int				ft_printadr(t_form *info, va_list args);

#endif
