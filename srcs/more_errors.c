/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:09:09 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/02 12:11:36 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tree.h"
#include "builtins.h"

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
