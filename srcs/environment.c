/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:45:16 by daprovin          #+#    #+#             */
/*   Updated: 2020/11/28 02:49:41 by daprovin         ###   ########.fr       */
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
	int		i;
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
