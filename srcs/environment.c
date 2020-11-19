/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:45:16 by daprovin          #+#    #+#             */
/*   Updated: 2020/11/19 19:47:38 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "tree.h"

void		save_return(int ret)
{
	if (ret > 255)
		ret = ret % 255;
	free(g_data[RET]);
	g_data[RET] = (char*)sec(ft_itoa(ret));
}

int		init_env(char **envp)
{
	int 	i;
//	int	j;
//	char	*tmp;
	char	**data;
	t_env	*new;

	i = 0;
	while (envp[i] != NULL)
	{
		data = (char**)sec(ft_split(envp[i], '='));
		new = (t_env*)sec(malloc(sizeof(t_env)));
		new->name = data[0];
		new->value = join_value(data);
		new->stat = 0;
		new->next = NULL;
		add_env(new);
		free(data);
		i++;
	}
	return (0);
}

static int	change_env_value(char **data, int stat)
{
	t_env	*lst;

	lst = g_env;
	while (lst != NULL)
	{
		if (ft_strcmp(lst->name, data[0]) == 0)
		{
			if (stat == 1)
			{
				free(data[0]);
				free(data[1]);
				return (0);
			}
			free(lst->value);
			lst->value = join_value(data);
			lst->stat = stat;
			free(data[0]);
			return (0);
		}
		lst = lst->next;
	}
	return (1);
}

static int	c_tmp(char **tmp, char *name)
{
	int	i;

	i = 0;
	while (tmp[i] != NULL)
	{
		if (ft_strcmp(tmp[i], name) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	init_tmp(char ***tmp, int l)
{
	int	i;

	i = 0;
	while (i < l)
	{
		(*tmp)[i] = NULL;
		i++;
	}
}

static int	print_export(void)
{
	int	l;
	t_env	*lst;
	t_env	*prnt;
	char	**tmp;
	int	i;

	l = 0;
	lst = g_env;
	while (lst != NULL)
	{
		lst = lst->next;
		l++;
	}
	tmp = (char **)sec(malloc(sizeof(char*) * l));
	init_tmp(&tmp, l);
	i = 0;
	while (i < l)
	{
		lst = g_env;
		prnt = NULL;
		while (lst != NULL)
		{
			if (prnt == NULL && c_tmp(tmp, lst->name) == 0)
				prnt = lst;
			if (prnt != NULL)
				if (ft_strcmp(prnt->name,lst->name) > 0 && c_tmp(tmp, lst->name) == 0)
				prnt = lst;
			lst = lst->next;
		}
		ft_printf("%s=%s\n", prnt->name, prnt->value);
		tmp[i] = prnt->name;
		i++;
	}

	free(tmp);
	return (0);
}

int		ft_export(char **args)
{
	int		i;
	char	**data;
	t_env	*new;
//	char	*value;
	int	stat;

	i = 1;
	if (args[1] == NULL)
		print_export();
	while (args[i] != NULL)
	{
		stat = ft_isinstr('=', args[i]) ? 0 : 1;
		data = (char**)sec(ft_split(args[i], '='));
		/* if (check_data(data)) */
		/* 	error; */
		if (change_env_value(data, stat))
		{	
			new = (t_env*)sec(malloc(sizeof(t_env)));
			new->name = data[0];
			new->value = join_value(data);
			new->stat = stat;
			new->next = NULL;
			add_env(new);
		}
		free(data);
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
		ft_putstr_fd("vsh: unset: not enough arguments\n", 2);
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
		ft_putstr_fd("vsh: env: too many arguments\n", 2);
	list = g_env;
	while(list != NULL)
	{
		if (list->stat == 0)
			ft_printf("%s=%s\n", list->name, list->value);
		list = list->next;
	}
	return (0);
}
