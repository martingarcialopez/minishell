/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:59:35 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/11/28 15:52:36 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include "tree.h"

static int	update_env_exp(char *name, char *value)
{
	t_env	*lst;

	lst = g_env;
	while (lst != NULL)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			free(lst->value);
			lst->value = (char*)sec(ft_strdup(value));
			break ;
		}
		lst = lst->next;
	}
	if (lst == NULL)
		return (1);
	return (0);
}

static int	update_env(void)
{
	char	*tmp;
	char	*buf;

	tmp = g_data[PWD];
	buf = NULL;
	buf = getcwd(buf, 0);
	g_data[PWD] = buf;
	if (update_env_exp("PWD", g_data[PWD]))
		new_env("PWD", g_data[PWD], 0);
	if (update_env_exp("OLDPWD", tmp))
		new_env("OLDPWD", tmp, 0);
	free(g_data[OLDPWD]);
	g_data[OLDPWD] = (char*)sec(ft_strdup(tmp));
	free(tmp);
	return (0);
}

static char	*join_home(char *home, char *args)
{
	char	*ret;

	args++;
	ret = (char*)sec(ft_strjoin(home, args));
	return (ret);
}

void		cd_exp(char **arg, char *home)
{
	char	*tmp;

	tmp = *arg;
	*arg = join_home(home, *arg);
	free(tmp);
}

int			ft_cd(char **args)
{
	int		i;
	char	*home;

	home = NULL;
	if (retrieve_env_variable("HOME", &home) == 0)
		i = -2;
	else if (args[1] == NULL)
		i = chdir(home);
	else if (args[1] != NULL && *args[1] == '~' && args[1][1] != '-')
		cd_exp(&(args[1]), home);
	if (args[1] != NULL && ft_strcmp(args[1], "~-") == 0)
		i = chdir(g_data[OLDPWD]);
	else if (args[1] != NULL && args[1][0] == '-' && args[1][1] == '\0')
		i = print_relative_path(home);
	else if (args[1] != NULL)
		i = chdir(args[1]);
	if (i == -1)
		ft_printf_fd(2, "%s: cd: %s\n", g_data[ARGV0], strerror(errno));
	if (i == 0)
		update_env();
	if (i == -2)
		ft_printf_fd(2, "%s: cd: HOME not set\n", g_data[ARGV0]);
	free(home);
	i = (i == 0) ? 0 : 1;
	return (i);
}
