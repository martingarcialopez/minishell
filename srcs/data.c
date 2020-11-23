#include "libft.h"
#include "builtins.h"
#include "tree.h"


int	init_data(char **argv)
{
	t_env	*list;
	int	i;

	list = g_env;
	while (list != NULL)
	{
		if (ft_strcmp(list->name, "PWD") == 0)
			g_data[PWD] = ft_strdup(list->value);
		else if (ft_strcmp(list->name, "OLDPWD") == 0)
			g_data[OLDPWD] = ft_strdup(list->value); //securizar
		list = list->next;
	}
	g_data[ARGV0] = argv[0];
	i = 0;
	// gestionar ./minishell -c 'cat < doesnotexist' idonthaveslash
	while (*(g_data[ARGV0] + i))
	    i++;
	while (*(g_data[ARGV0] + i) != '/')
	    i--;
	g_data[ARGV0] = (g_data[ARGV0] + ++i);
	g_ret = 0;
	return (0);
}
