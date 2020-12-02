/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:04:09 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/02 11:51:34 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include "tree.h"

int			print_relative_path(char *home)
{
	int		r;
	int		i;
	char	*str;
	char	*tmp;

	str = (char*)sec(ft_strdup(g_data[OLDPWD]));
	r = chdir(g_data[OLDPWD]);
	i = 0;
	if (home != NULL)
	{
		while (*(home + i) == *(str + i) && *(home + i) != '\0' &&
		*(str + i) != '\0')
			i++;
		if (strlen(home) <= strlen(str))
		{
			tmp = str;
			str = (char*)sec(ft_strjoin("~", (str + i)));
			free(tmp);
		}
	}
	ft_printf("%s\n", str);
	free(str);
	return (r);
}

void		new_env(char *name, char *value, int stat)
{
	t_env	*new;

	new = (t_env*)sec(malloc(sizeof(t_env)));
	new->name = (char*)sec(ft_strdup(name));
	new->value = (char*)sec(ft_strdup(value));
	new->next = NULL;
	new->stat = stat;
	add_env(new);
}

int			ft_pwd(char **args)
{
	char	*buf;

	if (args[1] != NULL)
		args[1] = args[1];
	buf = NULL;
	buf = getcwd(buf, 0);
	ft_printf("%s\n", buf);
	free(buf);
	return (0);
}

int			ft_echo(char **args)
{
	int		i[3];

	i[0] = 1;
	i[1] = 0;
	i[2] = 0;
	while (args[i[0]] != NULL && args[i[0]][0] == '-')
	{
		i[2] = 1;
		while (args[i[0]][i[2]] == 'n')
			i[2]++;
		if (args[i[0]][i[2]] == '\0')
			i[1] = 1;
		else
			break ;
		i[0]++;
	}
	while (args[i[0]] != NULL)
	{
		ft_printf("%s", args[i[0]++]);
		if (args[i[0]] != NULL)
			ft_printf(" ");
	}
	if (i[1] == 0)
		ft_printf("\n");
	return (0);
}

int			ft_exit(char **args)
{
	int		i;

	(void)args;
	ft_printf("exit\n");
	if (!args[1])
		exit(0);
	if (args[2] != NULL)
	{
		ft_printf_fd(2, "%s: exit: too many arguments\n", g_data[ARGV0]);
		return (1);
	}
	i = (args[1][0] == '-') ? 0 : -1;
	while (args[1][++i] != '\0')
		if (!ft_isdigit(args[1][i]))
		{
			ft_printf_fd(2, "%s: exit: %s: numeric argument required\n",
						g_data[ARGV0], args[1]);
			return (EXIT_ERROR);
		}
	exit(atoi(args[1]));
}
