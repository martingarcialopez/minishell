/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:04:22 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/07 15:45:14 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include <fcntl.h>
#include <sys/stat.h>

static void		redirect_and_exec_cmd(int fd, int to_dup, t_tree *tree)
{
	int		status;

	if (tree->right)
	{
		dup2(fd, to_dup);
		close(fd);
		status = exec_commands(tree->left);
		exit(status > 255 ? status / 256 : status);
	}
	exit(0);
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
		return (open_error(file));
	fk = fork();
	if (fk == 0)
		redirect_and_exec_cmd(fd, 1, tree);
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
		return (open_error(file));
	fk = fork();
	if (fk == 0)
		redirect_and_exec_cmd(fd, 1, tree);
	else if (fk > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
			return (status);
	}
	return (error_fork_failed());
}

static int		left_redirection(t_tree *tree)
{
	int			fk;
	int			fd;
	int			status;
	char		*file;

	if (tree->right)
		file = tree->right->data[0];
	else
		file = tree->left->data[0];
	if ((fd = open(file, O_RDONLY)) < 0)
		return (open_error(file));
	fk = fork();
	if (fk == 0)
		redirect_and_exec_cmd(fd, 0, tree);
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
