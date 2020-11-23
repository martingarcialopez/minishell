#include "builtins.h"
#include "tree.h"
#include <fcntl.h>
#include <sys/stat.h>

int			error(char *err)
{
    ft_printf_fd(2, "%s: %s: %s\n", g_data[ARGV0], err, strerror(errno));
    return (errno);
}

int			error_fork_failed(void)
{
    ft_printf_fd(2, "%s: error: %s\n", g_data[ARGV0], strerror(errno));
    return (1);
}

static int		right_redirection(t_tree *tree)
{
    int			fk;
    int			fd;
    int			status;

    if ((fd = open(tree->right->data[0], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
	return (error(tree->right->data[0]));
    fk = fork();
    if (fk == 0)
    {
	dup2(fd, 1);
	close(fd);
	exit(exec_commands(tree->left));
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

    if ((fd = open(tree->right->data[0], O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
	return (error(tree->right->data[0]));
    fk = fork();
    if (fk == 0)
    {
	dup2(fd, 1);
	close(fd);
	exit(exec_commands(tree->left));
    }
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

    if ((fd = open(tree->right->data[0], O_RDONLY)) < 0)
	return (error(tree->right->data[0]));
    fk = fork();
    if (fk == 0)
    {
	dup2(fd, 0);
	close(fd);
	exit(exec_commands(tree->left));
    }
    else if (fk > 0)
    {
	wait(&status);
	if (WIFEXITED(status))
	    return (status);
    }
    return (error_fork_failed());
}

int		redirection(t_tree *tree)
{
    if (tree->type == right_redir)
	return (right_redirection(tree));
    if (tree->type == double_right_redir)
	return (double_right_redirection(tree));
    if (tree->type == left_redir)
	return (left_redirection(tree));
    return (1);
}
