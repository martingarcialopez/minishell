#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include "tree.h"

int		ft_pwd(char **args)
{
	char	*buf;
	t_env	*list;

	if (args[1] != NULL)
	{
		//strerror();
		return (1);
	}
	buf = NULL;
	buf = getcwd(buf, 0);
	ft_printf("%s\n", buf);
	free(buf);
	return (0);
}

void new_env(char *name, char *value)
{
	t_env	*new;

	new = (t_env*)malloc(sizeof(t_env)); //securizar
	new->name = ft_strdup(name); //securizar
	new->value = ft_strdup(value); //securizar
	new->next = NULL;
	add_env(new);
}

const int	update_env(void)
{
	t_env	*lst;
	char	*tmp;
	char	*buf;

	lst = g_env;
	tmp = g_data[PWD];
	buf = NULL;
	buf = getcwd(buf, 0);
	g_data[PWD] = buf;
	while (lst != NULL)
	{
		if (ft_strcmp(lst->name, "PWD") == 0)
		{
			free(lst->value);
			lst->value = ft_strdup(g_data[PWD]); //securizar
			break;
		}
		lst = lst->next;
	}
	if (lst == NULL)
		new_env("PWD", g_data[PWD]);
	lst = g_env;
	while (lst != NULL)
	{
		if (ft_strcmp(lst->name, "OLDPWD") == 0)
		{
			free(lst->value);
			lst->value = tmp;
			break;
		}
		lst = lst->next;
	}
	if (lst == NULL)
		new_env("OLDPWD", tmp);
	return 0;
}

int		ft_cd(char **args)
{
	int	i;
	char	*home;

	if (retrieve_env_variable("HOME", &home) == 0)
		i = 0;
	else if (args[1] == NULL)
		i = chdir("\0");
	if (args[1] != NULL)
		i = chdir(args[1]);
	if (i == -1)
		ft_printf("cd: %s\n",strerror(errno));
	if (i == 0)
		update_env();
	return (i * (-1));
}

int		ft_echo(char **args)
{
	int	i;

	i = 1;
	if (args[1] == NULL)
		return (0);
	if (ft_strcmp("-n", args[1]) == 0)
		while (args[i + 1] != NULL)
		{
			ft_printf("%s", args[1 + i++]);
			if (args[1 + i] != NULL)
				ft_printf(" ");
		}
	else
	{
		while (args[i] != NULL)
		{
			ft_printf("%s", args[i++]);
			if (args[i] != NULL)
				ft_printf(" ");
		}
		ft_printf("\n");
	}
	return (0);
}

int		ft_exit(char **args)
{
	ft_printf("exit\n");
	exit(0);
}
