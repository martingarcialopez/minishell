/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:04:22 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/01 14:03:53 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include <fcntl.h>
#include <sys/stat.h>

#define EACCES_EXIT_STATUS 126
#define ENOENT_EXIT_STATUS 127

static int		error(char *err)
{
	ft_printf_fd(2, "%s: %s: %s\n", g_data[ARGV0], err, strerror(errno));
	if (errno == EACCES)
		return (EACCES_EXIT_STATUS);
	else
		return (1);
}

static int		error_fork_failed(void)
{
	ft_printf_fd(2, "%s: error: %s\n", g_data[ARGV0], strerror(errno));
	return (1);
}

static int		right_redirection(t_tree *tree)
{
	int			fk;
	int			fd;
	int			status;
	char		*file;

	if (tree->right)
		file = tree->right->data[0];
	else
		file = tree->left->data[0];
	if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		return (error(file));
	fk = fork();
	if (fk == 0)
	{
		if (tree->right)
		{
			dup2(fd, 1);
			close(fd);
			status = exec_commands(tree->left);
			exit(status > 255 ? status / 256 : status);
		}
		exit(0);
	}
	else if (fk > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
			return (status);
	}
	return (error_fork_failed());
}

static int		double_right_redirection(t_tree *tree)
{
	int			fk;
	int			fd;
	int			status;
	char		*file;

	if (tree->right)
		file = tree->right->data[0];
	else
		file = tree->left->data[0];
	if ((fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
		return (error(file));
	fk = fork();
	if (fk == 0)
	{
		if (tree->right)
		{
			dup2(fd, 1);
			close(fd);
			status = exec_commands(tree->left);
			exit(status > 255 ? status / 256 : status);
		}
		exit(0);
	}
	else if (fk > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			return (status);
		}
	}
	return (error_fork_failed());
}

static int		left_redirection(t_tree *tree)
{
	int			fk;
	int			fd;
	int			status;

	if ((fd = open(tree->right->data[0], O_RDWR)) < 0)
		return (error(tree->right->data[0]));
	fk = fork();
	if (fk == 0)
	{
		dup2(fd, 0);
		close(fd);
		status = exec_commands(tree->left);
		exit(status > 255 ? status / 256 : status);
	}
	else if (fk > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
			return (status);
	}
	return (error_fork_failed());
}

int				redirection(t_tree *tree)
{
	if (tree->type == right_redir)
		return (right_redirection(tree));
	if (tree->type == double_right_redir)
		return (double_right_redirection(tree));
	if (tree->type == left_redir)
		return (left_redirection(tree));
	return (1);
}
