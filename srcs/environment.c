/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:45:16 by daprovin          #+#    #+#             */
/*   Updated: 2020/11/03 23:56:27 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

void		save_return(int ret)
{
	t_env	*lst;

	lst = g_env;
	while (lst != NULL && ft_strcmp(lst->name, "?") != 0)
		lst = lst->next;
	if (lst == NULL)
	{
		lst = (t_env*)malloc(sizeof(t_env));//securizar
		lst->name = ft_strdup("?");//securizar
		lst->value = ft_strdup(ft_itoa(ret));//securizar
		add_env(lst);
	}
	else
	{
		free(lst->value);
		lst->value = ft_strdup(ft_itoa(ret));
	}
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
	new = (t_env*)malloc(sizeof(t_env));//securizar
	new->name = ft_strdup("?");
	new->value = ft_strdup("0");
	new->next = NULL;
	add_env(new);
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
		if (ft_strcmp(list->name, "?") != 0)
			ft_printf("%s=%s\n", list->name, list->value);
		list = list->next;
	}
	return (0);
}
