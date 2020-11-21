#include "libft.h"
#include "tree.h"
#include "builtins.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

char			*error_retrieving_env_variable(char *var)
{
    ft_printf_fd(2, "%s: error: %s variable not found in env\n", g_data[ARGV0], var);
    return (NULL);
}

void			parse_error(int err_type, void *value, t_list **alst)
{
    ft_printf_fd(2, "%s: parse error", g_data[ARGV0]);
    if (err_type == 0)
	ft_printf_fd(2, " near `%c'\n", *((char*)value));
    else if (err_type == 1)
	ft_printf_fd(2, " near `%s'\n", (char*)value);
    else if (err_type == 2)
	ft_printf_fd(2, ": missing quote(%c)\n", ((char*)value)[0]);
    ft_lstclear(alst, &free_token);
}

void			free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab[i]);
	free(tab);
}

int	retrieve_env_variable(char *name, char **value)
{
	t_env	*list;
	
	list = g_env;
	if (ft_strcmp("PWD", name) == 0)
	{
		*value = sec(ft_strdup(g_data[PWD]));
		return (1);
	}
	else if (ft_strcmp("RET", name) == 0 || ft_strcmp("?", name) == 0)
	{
		*value = sec(ft_itoa(g_ret));
		return (1);
	}
	while (list)
	{
		if (ft_strcmp(list->name, name) == 0)
		{
			*value = sec(ft_strdup(list->value));
			return(1);
		}
		list = list->next;	
	}	
	return (0);	
}

void	*sec(void *ptr)
{
	if (ptr == NULL)
	{
		ft_printf_fd(2, "%s: error", g_data[ARGV0]);
		perror("");
		exit(1);	
	}
	return (ptr);
}
