/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:14:21 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/02 16:08:20 by mgarcia-         ###   ########.fr       */
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

int				error(char *err)
{
	ft_printf_fd(2, "%s: %s: %s\n", g_data[ARGV0], err, strerror(errno));
	if (errno == EACCES)
		return (EACCES_EXIT_STATUS);
	else if (errno == ENOENT)
		return (ENOENT_EXIT_STATUS);
	else
		return (1);
}

char			*error_retrieving_env_variable(char *var)
{
	ft_printf_fd(2, "%s: error: %s variable not found in env\n",
							g_data[ARGV0], var);
	return (NULL);
}

void			parse_error(int err_type, void *value, t_list **alst)
{
	ft_printf_fd(2, "%s: syntax error", g_data[ARGV0]);
	if (err_type == 0)
		ft_printf_fd(2, " near unexpected token `%c'\n", *((char*)value));
	else if (err_type == 1)
		ft_printf_fd(2, " near unexpected token `%s'\n", (char*)value);
	else if (err_type == 2)
		ft_printf_fd(2, ": missing quote(%c)\n", ((char*)value)[0]);
	ft_lstclear(alst, &free_token);
}
