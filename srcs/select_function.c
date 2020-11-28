/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:04:37 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/11/28 03:06:27 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "tree.h"

static t_bint_fnc	g_builtin_fnc[] =
{
	{"env", &ft_env},
	{"export", &ft_export},
	{"unset", &ft_unset},
	{"pwd", &ft_pwd},
	{"cd", &ft_cd},
	{"echo", &ft_echo},
	{"exit", &ft_exit},
	{NULL, 0}
};

char				*ft_superjoin(char **str)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = (char*)sec(ft_strdup(""));
	while (str[i] != NULL)
	{
		tmp = ret;
		ret = (char*)sec(ft_strjoin(ret, str[i]));
		free(tmp);
		i++;
	}
	return (ret);
}

char				**env_to_vect(void)
{
	t_env	*lst;
	char	**newenv;
	int		l;
	int		i;
	char	*tmp;

	lst = g_env;
	l = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		l++;
	}
	newenv = (char**)sec(malloc(sizeof(char*) * (l + 1)));
	i = -1;
	newenv[l] = NULL;
	lst = g_env;
	while (++i < l)
	{
		tmp = (char*)sec(ft_strjoin(lst->name, "="));
		newenv[i] = (char*)sec(ft_strjoin(tmp, lst->value));
		free(tmp);
		lst = lst->next;
	}
	return (newenv);
}

int					function(char **args)
{
	int		i;

	if (args[0] == NULL)
		return (1);
	i = 0;
	while (g_builtin_fnc[i].name != NULL)
	{
		if (ft_strcmp(args[0], g_builtin_fnc[i].name) == 0)
			return ((*g_builtin_fnc[i].fnct)(args));
		i++;
	}
	return (call_system_function(args));
}
