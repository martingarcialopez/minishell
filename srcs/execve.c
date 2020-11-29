/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:00:11 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/11/25 19:21:24 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define EACCES_EXIT_STATUS 126
#define ENOENT_EXIT_STATUS 127

static int			    error(char *err)
{
	ft_printf_fd(2, "%s: %s: %s\n", g_data[ARGV0], err, strerror(errno));
	if (errno == EACCES)
		return (EACCES_EXIT_STATUS);
	else if (errno == ENOENT)
		return (ENOENT_EXIT_STATUS);
	else
		return (1);
}

int		call_system_function(char **args)
{
	char	**env;
	char	*abs_path;
	int		fk;
	int		status;

	if ((abs_path = solve_cmd_path(args)) == NULL)
		return (g_ret);
	env = env_to_vect();
	fk = fork();
	if (fk == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(abs_path, args, env);
		exit(error(abs_path));
	}
	else if (fk > 0)
	{
		signal(SIGINT, SIG_IGN);
		free(abs_path);
		free_tab(env);
		wait(&status);
		signal(SIGINT, &signal_handler);
		if (WIFSIGNALED(status))
		{
			ft_printf("\n");
			return (status);
		}
		if (WIFEXITED(status))
			return (status);
	}
	free_tab(env);
	ft_printf_fd(2, "%s: error: could not fork process\n", g_data[ARGV0]);
	return (1);
}
