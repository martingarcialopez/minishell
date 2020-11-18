#include "libft.h"
#include "builtins.h"
#include "tree.h"


int	init_data(void)
{
	t_env	*list;

	list = g_env;
	while (list != NULL)
	{
		if (ft_strcmp(list->name, "PWD") == 0)
			g_data[PWD] = ft_strdup(list->value);
		else if (ft_strcmp(list->name, "OLDPWD") == 0)
			g_data[OLDPWD] = ft_strdup(list->value); //securizar
		list = list->next;
	}
	g_data[RET] = ft_strdup("0"); //securizar
	return (0);
}
