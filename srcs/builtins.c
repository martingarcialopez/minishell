#include "builtins.h"
#include "libft.h"

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

const int	update_env(void)
{
	t_env	*lst;
	char	*buf;
	char	*tmp;

	lst = g_env;
	buf = NULL;
	buf = getcwd(buf, 0);
	while (lst != NULL)
	{
		if (ft_strcmp(lst->name, "PWD") == 0)
		{
			tmp = lst->value;
			lst->value = buf;
			break;
		}
		lst = lst->next;
	}
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
	//add PWD if there is no
	return 0;
}

int		ft_cd(char **args)
{
	int	i;

	if (args[1] == NULL)
		i = chdir("~");
	else
		i = chdir(args[1]);
	if (i == -1)
		ft_printf("cd: %s\n",strerror(errno));
	if (i == 0)
		update_env();
	return (i);
}

int		ft_echo(char **args) //se puede hacer con un join para printear todo a la vez, preguntar a martin por las pipes
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
