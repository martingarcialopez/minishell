#include "builtins.h"
#include "libft.h"
#include "tree.h"

int		ft_unset(char **args)
{
	int		i;
	t_env	*list;

	i = 0;
	if (args[1] == NULL)
		return (0);
	while (args[++i] != NULL)
	{
		list = g_env;
		if (ft_strcmp(list->name, args[i]) == 0 && list != NULL)
		{
			g_env = g_env->next;
			lst_free(list);
		}
		else
			while (list != NULL && list->next != NULL)
			{
				if (ft_strcmp(list->next->name, args[i]) == 0)
					list_rm_next(list);
				list = list->next;
			}
	}
	return (0);
}
