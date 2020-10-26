/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:45:16 by daprovin          #+#    #+#             */
/*   Updated: 2020/10/26 17:41:43 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "../headers/libft.h"


typedef struct	s_env
{
	char 				*name;
	char				*value;
	struct s_env		*next;
}				t_env;

void	add_env(t_env **env, t_env  *new)
{
	t_env	*list;

	list = *env;
	if (list == NULL)
	{
		*env = new;
		return ;
	}
	while (list->next != NULL)
		list = list->next;
	list->next = new;
}

int		init_env(char **envp, t_env **env)
{
	int 	i;
	char	**data;
	t_env	*new;

	i = 0;
	while (envp[i] != NULL)
	{
		data = ft_split(envp[i], 'n');
		new = (t_env*)malloc(sizeof(t_env));
		new->name = data[0];
		new->value = data[1];
		new->next = NULL;
		add_env(env, new);
		free(data);
		i++;
	}
	return (0);
}
