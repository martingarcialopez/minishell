/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:45:16 by daprovin          #+#    #+#             */
/*   Updated: 2020/11/27 21:37:48 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "tree.h"

void		save_return(int ret)
{
	if (ret > 255)
		ret = ret % 255;
	g_ret = ret;
}

void		no_env(void)
{
	t_env	*new;

	new = (t_env*)sec(malloc(sizeof(t_env)));
	new->name = (char*)sec(ft_strdup("PWD"));
	new->value = NULL;
	new->value = getcwd(new->value, 0);
	new->stat = 0;
	new->next = NULL;
	add_env(new);
	new = (t_env*)sec(malloc(sizeof(t_env)));
	new->name = (char*)sec(ft_strdup("OLDPWD"));
	new->value = (char*)sec(ft_strdup(""));
	new->stat = 0;
	new->next = NULL;
	add_env(new);
}

int		init_env(char **envp)
{
	int 	i;
	char	**data;
	t_env	*new;

	i = 0;
	if (envp[i] == NULL)
		no_env();
	else
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

static void	init_tmp(char ***tmp, int l[2])
{
	t_env	*lst;

	l[0] = 0;
	l[1] = 0;
	lst = g_env;
	while (lst != NULL)
	{
		lst = lst->next;
		l[0]++;
	}
	*tmp = (char **)sec(malloc(sizeof(char *) * l[0]));
	while (l[1] < l[0])
		(*tmp)[l[1]++] = NULL;
	l[1] = 0;
}

static int	print_export(void)
{
	int	l[2];
	t_env	*lst;
	t_env	*p;
	char	**tmp;

	/* l = 0; */
	/* lst = g_env; */
	/* while (lst != NULL) */
	/* { */
	/* 	lst = lst->next; */
	/* 	l++; */
	/* } */
	/* tmp = (char **)sec(malloc(sizeof(char*) * l)); */
	init_tmp(&tmp, l);
	while (l[1] < l[0])
	{
		lst = g_env;
		p = NULL;
		while (lst != NULL)
		{
			if (!c_tmp(tmp, lst->name) && (!p ||
					ft_strcmp(p->name, lst->name) > 0))
				p = lst;
			/* if (prnt == NULL && c_tmp(tmp, lst->name) == 0) */
			/* 	prnt = lst; */
			/* if (prnt != NULL) */
			/* 	if (ft_strcmp(prnt->name,lst->name) > 0 && c_tmp(tmp, lst->name) == 0) */
			/* 		prnt = lst; */
			lst = lst->next;
		}
		if (p->stat == 0)
			ft_printf("declare -x %s=\"%s\"\n", p->name, p->value);
		else
			ft_printf("declare -x %s\n", p->name);
		tmp[l[1]++] = p->name;
	}
	free(tmp);
	return (0);
}

static int	check_args(char **args)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		if (*args[i] == '?' || *args[i] == '/' || *args[i] == '$')
		{
			ft_printf_fd(2, ERROR_IDENTIFIER,
					g_data[ARGV0], args[i]);
			return (1);
		}
		else if (*args[i] == '=')
		{
			if (*(args[i] + 1) == '\0')
				ft_printf_fd(2, ERROR_ASSIGNMENT,
						g_data[ARGV0]);
			else
				ft_printf_fd(2, ERROR_NFOUND, g_data[ARGV0],
						args[i] + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int		ft_export(char **args)
{
	int		i;
	char	**data;
	t_env	*new;
	int	stat;

	if (args[1] == NULL)
		print_export();
	if (check_args(args))
		return (1);
	i = 1;
	while (args[i] != NULL)
	{
		stat = ft_isinstr('=', args[i]) ? 0 : 1;
		data = (char**)sec(ft_split(args[i], '='));
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

	i = 0;
	if (args[1] == NULL)
		ft_printf_fd(2, "%s: unset: not enough arguments\n", g_data[ARGV0]);
	while (args[++i] != NULL)
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
					break ;
				}
				list = list->next;
			}
		//i++
	}
	return (0);
}

int		ft_env(char **args)
{
	t_env	*list;

	if (args[1] != NULL)
		ft_printf_fd(2, "%s: env: too many arguments\n", g_data[ARGV0]);
	list = g_env;
	while (list != NULL)
	{
		if (list->stat == 0)
			ft_printf("%s=%s\n", list->name, list->value);
		list = list->next;
	}
	return (0);
}
