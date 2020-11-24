#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include "tree.h"

int		ft_pwd(char **args)
{
	char	*buf;

	if (args[1] != NULL)
	{
		ft_printf_fd(2, "zsh: pwd: %s\n", strerror(errno));
		return (1);
	}
	buf = NULL;
	buf = getcwd(buf, 0);
	ft_printf("%s\n", buf);
	free(buf);
	return (0);
}

void 		new_env(char *name, char *value)
{
	t_env	*new;
	new = (t_env*)sec(malloc(sizeof(t_env))); 
	new->name = (char*)sec(ft_strdup(name));
	new->value = (char*)sec(ft_strdup(value));
	new->next = NULL;
	add_env(new);
}

static int	update_env(void)
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
			lst->value = (char*)sec(ft_strdup(g_data[PWD]));
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
	free(g_data[OLDPWD]);
	g_data[OLDPWD] = (char*)sec(ft_strdup(tmp));
	return 0;
}

static char	*join_home(char *home, char *args)
{
	char	*ret;
	
	args++;
	ret = (char*)sec(ft_strjoin(home, args));
	return (ret);
}

int		print_relative_path(char *home)
{
	int	r;
	int	i;
	char	*str;
	char	*tmp;

	str = (char*)sec(ft_strdup(g_data[OLDPWD]));
	r = chdir(g_data[OLDPWD]);
	i = 0;
	if (home != NULL)
	{
		while (*(home + i) == *(str + i) && *(home + i) != '\0' && *(str + i) != '\0')
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

int		ft_cd(char **args)
{
	int	i;
	char	*home;
	char	*tmp;

	home = NULL;
	if (retrieve_env_variable("HOME", &home) == 0)
		i = 0;
	else if (args[1] == NULL)
		i = chdir(home);
	else if (args[1] != NULL && *args[1] == '~' && args[1][1] != '-')
	{
		tmp = args[1];
		args[1] = join_home(home, args[1]);
		free(tmp);
	}
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
	free(home);
	return (i * (-1));
}

int		ft_echo(char **args)
{
	int	i[3];

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
			break;
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

int		ft_exit(char **args)
{
	(void)args;
	ft_printf("exit\n");
	if (!args[1])
	    exit(0);
	exit(atoi(args[1]));
}
