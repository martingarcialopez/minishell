/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:45:16 by daprovin          #+#    #+#             */
/*   Updated: 2020/11/03 19:33:13 by daprovin         ###   ########.fr       */
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
	i = 2;
	while (data[i] != NULL)
	{
		tmp = value;
		value = ft_strjoin(value, "=");//securizar
		free(tmp);
		tmp = value;
		value = ft_strjoin(value, data[i]);//securizar
		free(tmp);
		i++;
	}
	return (value);
}

int		init_env(char **envp)
{
	int 	i;
	int	j;
	char	*tmp;
	char	**data;
	t_env	*new;

	i = 0;
	while (envp[i] != NULL)
	{
		data = ft_split(envp[i], '=');
		new = (t_env*)malloc(sizeof(t_env));//securizar
		new->name = data[0];
		new->value = join_value(data);
		new->next = NULL;
		add_env(new);
		free(data);//free all the split
		i++;
	}
	return (0);
}

int		ft_export(char **args)
{
	int		i;
	char	**data;
	t_env	*new;

	i = 1;
	if (args[1] == NULL)
	{
		//strerror();
	}
	while (args[i] != NULL)
	{
		data = ft_split(args[i], '=');
		/* if (check_data(data)) */
		/* 	error; */
		new = (t_env*)malloc(sizeof(t_env)); //securizar
		new->name = data[0];
		new->value = join_value(data);
		new->next = NULL;
		add_env(new);
		i++;
	}
	return (0);

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

int		ft_unset(char **args)
{
	int		i;
	t_env	*list;

	i = 1;
	if (args[1] == NULL)
	{
		//strerror();
	}
	while (args[i] != NULL)
	{
		list = g_env;
		if (ft_strcmp(list->name, args[i]) == 0 && list != NULL)
		{	
			g_env = g_env->next;
			lst_free(list);
		}
		else
			while (list != NULL && list->next != NULL)
			{
				if (ft_strcmp(list->next->name, args[i]) == 0)
				{
					list_rm_next(list);
					break;
				}
				list = list->next;
			}
		i++;
	}
	return (0);
}

int		ft_env(char **args)
{
	t_env	*list;

	if (args[1] != NULL)
	{
		//strerror();
	}
	list = g_env;
	while(list != NULL)
	{
		ft_printf("%s=%s\n", list->name, list->value);
		list = list->next;
	}
	return (0);
}
