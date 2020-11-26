/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:06:29 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/11/25 20:56:35 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tree.h"
#include "builtins.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

int				check_path_status(char *path)
{
	struct stat		stats;

	if (stat(path, &stats) == 0)
	{
		if (!(stats.st_mode & S_IFDIR))
			return (0);
		return (1);
	}
	return (2);
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

void			free_token(void *tkn)
{
	t_token *token;

	token = (t_token*)tkn;
	free(token->value);
	free(token);
}

int				retrieve_env_variable(char *name, char **value)
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
			return (1);
		}
		list = list->next;
	}
	return (0);
}

void			*sec(void *ptr)
{
	if (ptr == NULL)
	{
		ft_printf_fd(2, "%s: error", g_data[ARGV0]);
		perror("");
		exit(1);
	}
	return (ptr);
}
