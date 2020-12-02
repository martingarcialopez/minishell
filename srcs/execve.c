/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:00:11 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/02 12:11:48 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

static int					fork_failed(char **env, char *path)
{
	ft_printf_fd(2, "%s: error: %s\n", g_data[ARGV0], strerror(errno));
	free(env);
	free(path);
	return (1);
}

static int					print_newline_and_return_status(int status)
{
	ft_printf("\n");
	return (status);
}

static void					call_exec(char *path, char **args, char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, args, env);
	exit(error(path));
}

int							call_system_function(char **args)
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
		call_exec(abs_path, args, env);
	else if (fk > 0)
	{
		signal(SIGINT, SIG_IGN);
		free(abs_path);
		free_tab(env);
		wait(&status);
		signal(SIGINT, &signal_handler);
		if (WIFSIGNALED(status))
			return (print_newline_and_return_status(status));
		if (WIFEXITED(status))
			return (status);
	}
	return (fork_failed(env, abs_path));
}
