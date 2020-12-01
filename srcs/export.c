
#include "builtins.h"
#include "libft.h"
#include "tree.h"

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

static int	check_args(char **args)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		if (*args[i] == '?' || *args[i] == '/' || *args[i] == '$'
			|| *args[i] == '=')
		{
			ft_printf_fd(2, ERROR_IDENTIFIER,
					g_data[ARGV0], args[i]);
			return (1);
		}
		i++;
	}
	return (0);
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

static int	print_export(void)
{
	int		l[2];
	t_env	*lst;
	t_env	*p;
	char	**tmp;

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

int			ft_export(char **args)
{
	int		i;
	char	**data;
	int		stat;

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
			new_env_exp(data, stat);
		free(data);
		i++;
	}
	return (0);
}
