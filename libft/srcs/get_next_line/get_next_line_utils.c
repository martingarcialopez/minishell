/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:20:20 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/31 15:45:30 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*ft_ovread(char **line, char *content)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = content;
	free(*line);
	*line = ft_strjoin("", content);
	i = 0;
	while ((*line)[i] != '\n')
		i++;
	(*line)[i] = '\0';
	if (!(content = (char*)malloc(sizeof(char) * (ft_strlen(content) - i + 1))))
		return (NULL);
	j = 0;
	while (tmp[j + i])
	{
		content[j] = tmp[j + i + 1];
		j++;
	}
	free(tmp);
	return (content);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*join;

	if (!s1)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(join = (char*)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	i = 0;
	while (i < len1)
	{
		join[i] = s1[i];
		i++;
	}
	while (i <= len1 + len2)
	{
		join[i] = s2[i - len1];
		i++;
	}
	return (join);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int		ft_isinstr(char c, char const *s2)
{
	int i;

	i = 0;
	while (s2[i])
	{
		if (c == s2[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_freelst(int fd, t_statlst **lst)
{
	t_statlst	*tmp_current;
	t_statlst	*tmp_prev;

	tmp_current = *lst;
	tmp_prev = NULL;
	while (tmp_current)
	{
		if (tmp_current->fd == fd)
		{
			free(tmp_current->content);
			if (tmp_prev != NULL)
				tmp_prev->next = tmp_current->next;
			else
				*lst = tmp_current->next;
			free(tmp_current);
			break ;
		}
		tmp_prev = tmp_current;
		tmp_current = tmp_current->next;
	}
}
