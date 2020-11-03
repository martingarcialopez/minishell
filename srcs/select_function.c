#include "builtins.h"
#include "libft.h"

char	*ft_superjoin(char **str)//mallocs sin securizar;
{
	int	i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = ft_strdup("");
	while (str[i] != NULL)
	{
		tmp = ret;
		ret = ft_strjoin(ret, str[i]);
		free(tmp);
		i++;
	}
	return (ret);
}


void	solve_dollar(char ***args) //mallocs sin securizar;
{
	int	i;
	int	j;
	char	**spl;
	t_env	*lst;
	char	*tmp;

	i = 0;
	while ((*args)[i] != NULL)
	{
		/* ft_printf("holaaa\n"); */
		if (ft_isinstr('$', (*args)[i]))
		{
		/* ft_printf("holaaa\n"); */
			spl = ft_split((*args)[i], '$');
			j = 0;
			if (*(*args)[i] != '$')
				j++;
			while (spl[j] != NULL)
			{
				/* ft_printf("holaaa\n"); */
				lst = g_env;
				while (lst != NULL && ft_strcmp(lst->name, spl[j]) != 0)
					lst = lst->next;
				/* ft_printf("holaaa\n"); */
				tmp = spl[j];
				if (lst != NULL)
					spl[j] = ft_strdup(lst->value);
				else
					spl[j] = ft_strdup("");
				free(tmp);
				j++;
			}
				/* ft_printf("holaaa\n"); */
			(*args)[i] = ft_superjoin(spl);
				/* ft_printf("holaaa\n"); */
			free(spl);//hay que hacer free a todo el split
		}
		i++;
	}	
}

int	function(char **args)
{
	int	i;

	solve_dollar(&args);	
	if (args[0] == NULL)
		return (1);
	i = 0;
	while (g_builtin_fnc[i].name != NULL)
	{
		if(ft_strcmp(args[0], g_builtin_fnc[i].name) == 0)
			return((*g_builtin_fnc[i].fnct)(args));
		i++;
	}
	call_system_function(args);
	ft_printf("Error: command not found\n");
	return (1); //Si llega hastq aqui es que se chingo la wea
}
