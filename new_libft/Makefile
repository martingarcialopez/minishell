# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daprovin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 17:02:28 by daprovin          #+#    #+#              #
#    Updated: 2020/01/20 23:31:44 by daprovin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

OBJS := \
	ft_memset.o \
	ft_putchar_fd.o \
	ft_putendl_fd.o \
	ft_putnbr_fd.o \
	ft_putstr_fd.o \
	ft_strlcat.o \
	ft_strlcpy.o \
	ft_strlen.o \
	ft_strchr.o \
	ft_strrchr.o \
	ft_strncmp.o \
	ft_atoi.o \
	ft_isdigit.o \
	ft_isspace.o \
	ft_strnstr.o \
	ft_isalpha.o \
	ft_isalnum.o \
	ft_isascii.o \
	ft_isprint.o \
	ft_toupper.o \
	ft_tolower.o \
	ft_bzero.o \
	ft_memcpy.o \
	ft_memccpy.o \
	ft_memmove.o \
	ft_memchr.o \
	ft_memcmp.o \
	ft_calloc.o \
	ft_strdup.o \
	ft_substr.o \
	ft_strjoin.o \
	ft_isinstr.o \
	ft_strtrim.o \
	ft_countstrings.o \
	ft_doingmalloc.o \
	ft_split.o \
	ft_lengthnumb.o \
	ft_itoa.o \
	ft_strmapi.o \
	ft_fillstr.o \
	ft_doingfree.o \
	get_next_line.o \
	get_next_line_utils.o \
	ft_printf.o \
	ft_printf_utils.o \
	ft_printing_types.o \
	ft_printing_type_uint.o \
	ft_printing_type_point.o \
	ft_printing_type_int.o \
	ft_printing_type_hex.o \

OBJB := \
	ft_lstnew_bonus.o \
	ft_lstadd_front_bonus.o \
	ft_lstsize_bonus.o \
	ft_lstlast_bonus.o \
	ft_lstadd_back_bonus.o \
	ft_lstdelone_bonus.o \
	ft_lstclear_bonus.o \
	ft_lstiter_bonus.o \
	ft_lstmap_bonus.o \

GFLAGS := -Wall -Werror -Wextra
HEAD := headers

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

bonus : $(OBJS) $(OBJB)
	ar rc $(NAME) $(OBJB) $(OBJS)

%.o: %.c
	gcc $(GFLAGS) -I $(HEAD) -c $< -o $@

clean :
	rm -f $(OBJS) $(OBJB)

fclean : clean
	rm -f $(NAME)

re : fclean all
