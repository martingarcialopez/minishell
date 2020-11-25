/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:04:37 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/11/25 19:04:38 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "tree.h"

static t_bint_fnc	g_builtin_fnc[]=
{
	{"env", &ft_env},
	{"export", &ft_export},
	{"unset", &ft_unset},
	{"pwd", &ft_pwd},
	{"cd", &ft_cd},
	{"echo", &ft_echo},
	{"exit", &ft_exit},
	{NULL, 0}
};

char	*ft_superjoin(char **str)//mallocs sin securizar;
{
	int	i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = ft_strdup("");
	while (str[i] != NULL) {
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
		if (ft_isinstr('$', (*args)[i]))
		{
			spl = ft_split((*args)[i], '$');
			j = 0;
			if (*(*args)[i] != '$')
				j++;
			while (spl[j] != NULL)
			{
				lst = g_env;
				while (lst != NULL && ft_strcmp(lst->name, spl[j]) != 0)
					lst = lst->next;
				tmp = spl[j];
				if (lst != NULL)
					spl[j] = ft_strdup(lst->value);
				else
					spl[j] = ft_strdup("");
				free(tmp);
				j++;
			}
			(*args)[i] = ft_superjoin(spl);
			free(spl);//hay que hacer free a todo el split
		}
		i++;
	}	
}

char	**env_to_vect(void)
{
	t_env	*lst;
	char	**newenv;
	int	l;
	int	i;
	char	*tmp;

	lst = g_env;

	l = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		l++;
	}
	newenv = (char**)malloc(sizeof(char*) * (l + 1)); //securizar malloc
	i = 0;
	newenv[l] = NULL;
	lst = g_env;
	while (i < l)
	{
		newenv[i] = ft_strjoin(lst->name, "=");
		tmp = newenv[i];
		newenv[i] = ft_strjoin(newenv[i], lst->value);
		free(tmp);
		lst = lst->next;
		i++;
	}
	return (newenv);
}

int	function(char **args)
{
	int	i;
	
	//solve_dollar(&args);
	if (args[0] == NULL)
		return (1);
	i = 0;
	while (g_builtin_fnc[i].name != NULL)
	{
		if(ft_strcmp(args[0], g_builtin_fnc[i].name) == 0)
			return((*g_builtin_fnc[i].fnct)(args));
		i++;
	}
	return (call_system_function(args));
}
