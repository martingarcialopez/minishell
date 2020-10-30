/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 03:04:16 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/31 16:10:20 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

int		ft_isinlst(int fd, t_statlst **lst, char **line)
{
	t_statlst	*tmp_lst;
	char		*tmp_dst;

	tmp_lst = *lst;
	while (tmp_lst)
	{
		if (tmp_lst->fd == fd)
		{
			if (ft_isinstr('\n', tmp_lst->content))
			{
				tmp_lst->content = ft_ovread(line, tmp_lst->content);
				return (2);
			}
			tmp_dst = *line;
			*line = ft_strjoin(*line, tmp_lst->content);
			free(tmp_dst);
			return (1);
		}
		tmp_lst = tmp_lst->next;
	}
	return (0);
}

void	ft_lstnewback(int fd, t_statlst **lst)
{
	t_statlst *new;
	t_statlst *tmp_lst;

	tmp_lst = *lst;
	if (!(new = (t_statlst*)malloc(sizeof(t_statlst))))
		return ;
	new->fd = fd;
	new->next = NULL;
	new->content = ft_strjoin("", "");
	if (!tmp_lst)
	{
		*lst = new;
		return ;
	}
	while (tmp_lst->next)
		tmp_lst = tmp_lst->next;
	tmp_lst->next = new;
}

void	ft_changecontent(int fd, t_statlst **lst, char *dst)
{
	t_statlst	*tmp_lst;
	char		*tmp;
	int			i;
	int			j;
	int			l;

	tmp_lst = *lst;
	while (tmp_lst->fd != fd)
		tmp_lst = tmp_lst->next;
	i = 0;
	while (dst[i] != '\n')
		i++;
	tmp = tmp_lst->content;
	l = ft_strlen(dst);
	if (!(tmp_lst->content = (char*)malloc(sizeof(char) * (l - i))))
		return ;
	free(tmp);
	(tmp_lst->content)[l - i - 1] = '\0';
	j = 0;
	while (dst[i + 1])
	{
		(tmp_lst->content)[j] = dst[i + 1];
		i++;
		j++;
	}
}

int		ft_read(int fd, t_statlst **lst, char *buffer, char **line)
{
	int		i;
	int		rt;
	char	*tmp;

	while ((rt = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[rt] = '\0';
		tmp = *line;
		*line = ft_strjoin(*line, buffer);
		free(tmp);
		i = 0;
		while (*(*line + i) != '\n' && *(*line + i) != '\0')
			i++;
		*(*line + i) = '\0';
		if (ft_isinstr('\n', buffer))
		{
			ft_changecontent(fd, lst, buffer);
			break ;
		}
	}
	return (rt);
}

int		gnl(int fd, char **line)
{
	char				buffer[BUFFER_SIZE + 1];
	static t_statlst	*lst;
	int					rt;
	int					count;

	*line = ft_strjoin("", "");
	if ((count = ft_isinlst(fd, &lst, line)) == 2)
		return (1);
	if (!count)
		ft_lstnewback(fd, &lst);
	rt = ft_read(fd, &lst, buffer, line);
	if (rt == 0)
	{
		ft_freelst(fd, &lst);
		return (0);
	}
	if (rt > 0)
		return (1);
	return (-1);
}
