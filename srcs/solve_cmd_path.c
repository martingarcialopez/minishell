/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:06:05 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/11/25 20:46:41 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include "unistd.h"
#include <sys/wait.h>
#include <sys/stat.h>

char			*solve_abs_path(char **args)
{
	char	*abs_path;
	int		errnum;

	abs_path = sec(ft_strdup(args[0]));
	if ((errnum = check_path_status(abs_path)) == 0)
		return (abs_path);
	else if (errnum == 1)
		return (is_a_directory(abs_path));
	return (abs_path);
}

char			*solve_home(char *arg)
{
	char	*path;
	char	*abs_path;
	int		errnum;
	int		len;

	if (!(retrieve_env_variable("HOME", &path)))
		return (error_retrieving_env_variable("HOME"));
	len = ft_strlen(path) + ft_strlen(arg) + 1;
	abs_path = (char*)sec(malloc(sizeof(char) * len));
	abs_path[0] = '\0';
	ft_strcat(abs_path, path);
	ft_strcat(abs_path, ++arg);
	free(path);
	if ((errnum = check_path_status(abs_path)) == 0)
		return (abs_path);
	else if (errnum == 1)
		return (is_a_directory(abs_path));
	return (abs_path);
}

char			*solve_relative_path(char **args)
{
	char	*path;
	char	*abs_path;
	int		errnum;
	int		len;

	if (!(retrieve_env_variable("PWD", &path)))
		return (error_retrieving_env_variable("PWD"));
	len = ft_strlen(path) + ft_strlen(args[0]) + 1;
	abs_path = (char*)sec(malloc(sizeof(char) * len));
	abs_path[0] = '\0';
	ft_strcat(abs_path, path);
	ft_strcat(abs_path, (*args + 1));
	free(path);
	if ((errnum = check_path_status(abs_path)) == 0)
		return (abs_path);
	else if (errnum == 1)
		return (is_a_directory(abs_path));
	return (abs_path);
}

char			*find_path(char **args)
{
	char	*path;
	char	*abs_path;
	char	**split_path;
	int		len;
	int		i;

	if (!(retrieve_env_variable("PATH", &path)))
		return (error_retrieving_env_variable("PATH"));
	len = ft_strlen(path) + ft_strlen(args[0]) + 1;
	abs_path = (char*)sec(malloc(sizeof(char) * len));
	split_path = sec(ft_split(path, ':'));
	free(path);
	i = 0;
	while (split_path[i])
	{
		abs_path[0] = '\0';
		ft_strcat(abs_path, split_path[i]);
		ft_strcat(abs_path, "/");
		ft_strcat(abs_path, args[0]);
		if (check_path_status(abs_path) == 0)
			return (free_tab_and_return_path(split_path, abs_path));
		i++;
	}
	return (command_not_found(split_path, abs_path, args[0]));
}

char			*solve_cmd_path(char **args)
{
	if (args[0][0] == '/')
		return (solve_abs_path(args));
	else if (args[0][0] == '.')
		return (solve_abs_path(args));
	else if (args[0][0] == '~')
		return (solve_home(args[0]));
	else
		return (find_path(args));
}
