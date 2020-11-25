/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:00:03 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/11/25 19:00:04 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

void	add_env(t_env  *new)
{
	t_env	*list;

	list = g_env;
	if (list == NULL)
	{
		g_env = new;
		return ;
	}
	while (list->next != NULL)
		list = list->next;
	list->next = new;
}

char		*join_value(char **data)
{
	char	*value;
	int	i;
	char	*tmp;

	value = data[1];
	if (data[1] == NULL)
	{
		free(data[1]);
		value = ft_strdup("");//securizar
		return (value);
	}
	i = 2;
	while (data[i] != NULL)
	{
		tmp = value;
		value = ft_strjoin(value, "=");//securizar
		free(tmp);
		tmp = value;
		value = ft_strjoin(value, data[i]);//securizar
		free(tmp);
		free(data[i]);
		i++;
	}
	free(data[i]);
	return (value);
}

void	lst_free(t_env	*list)
{
		free(list->name);
		free(list->value);
		free(list);
}

void	list_rm_next(t_env *list)
{
	t_env	*aux;

	aux = list->next->next;
	lst_free(list->next);
	list->next = aux;
}
