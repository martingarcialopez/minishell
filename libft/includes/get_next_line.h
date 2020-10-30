/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 23:30:37 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/31 15:14:13 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_statlst
{
	int					fd;
	char				*content;
	struct s_statlst	*next;
}				t_statlst;

int				ft_isinlst(int fd, t_statlst **lst, char **line);
void			ft_lstnewback(int fd, t_statlst **lst);
void			ft_changecontent(int fd, t_statlst **lst, char *dst);
int				ft_read(int fd, t_statlst **lst, char *buffer, char **line);
int				get_next_line(int fd, char **line);
char			*ft_ovread(char **line, char *content);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *s);
int				ft_isinstr(char c, char const *s2);
void			ft_freelst(int fd, t_statlst **lst);

#endif
