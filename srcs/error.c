/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:14:21 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/02 09:36:33 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tree.h"
#include "builtins.h"

#define EACCES_EXIT_STATUS 126
#define ENOENT_EXIT_STATUS 127

int				open_error(char *err)
{
	ft_printf_fd(2, "%s: %s: %s\n", g_data[ARGV0], err, strerror(errno));
	if (errno == EACCES)
		return (EACCES_EXIT_STATUS);
	else
		return (1);
}

int				error_fork_failed(void)
{
	ft_printf_fd(2, "%s: error: %s\n", g_data[ARGV0], strerror(errno));
	return (1);
}

char			*command_not_found(char **tab, char *str, char *cmd)
{
	free_tab(tab);
	free(str);
	ft_printf_fd(2, "%s: %s: command not found\n", g_data[ARGV0], cmd);
	g_ret = 127;
	return (NULL);
}

char			*free_tab_and_return_path(char **tab, char *abs_path)
{
	free_tab(tab);
	return (abs_path);
}

char			*is_a_directory(char *path)
{
	ft_printf_fd(2, "%s: %s: is a directory\n", g_data[ARGV0], path);
	free(path);
	g_ret = 126;
	return (NULL);
}

char			*error_retrieving_env_variable(char *var)
{
	ft_printf_fd(2, "%s: error: %s variable not found in env\n",
							g_data[ARGV0], var);
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
