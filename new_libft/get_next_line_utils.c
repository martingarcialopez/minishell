/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:20:20 by daprovin          #+#    #+#             */
/*   Updated: 2020/01/20 19:19:10 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ovread(char **line, char *content)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = content;
	free(*line);
	if (!(*line = ft_strjoin("", content)))
		return (NULL);
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
