#include "../includes/builtins.h"
#include "../includes/libft.h"

int	function(char **args)
{
	int	i;

	i = 0;
	while (g_builtin_fnc[i].name != NULL)
	{
		if(ft_strcmp(args[0], g_builtin_fnc[i].name) == 0)
			return((*g_builtin_fnc[i].fnct)(args));
		i++;
	}
	return (0);
}
