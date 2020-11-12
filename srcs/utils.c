#include "libft.h"
#include "tree.h"
#include "builtins.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

int	retrieve_env_variable(char *name, char **value)
{
	t_env	*list;
	
	list = g_env;
	if (ft_strcmp("PWD", name) == 0)
	{
		*value = g_data[PWD];
		return (1);
	}
	else if (ft_strcmp("RET", name) == 0)
	{
		*value = g_data[RET];
		return (1);
	}
	while (list)
	{
		if (ft_strcmp(list->name, name) == 0)
		{
			*value = list->value;
			return(1);
		}
		list = list->next;	
	}	
	return (0);	
}
