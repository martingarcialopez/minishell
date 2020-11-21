#include "builtins.h"
#include "tree.h"
#include <fcntl.h>
#include <sys/stat.h>

static void		right_redirection(t_tree *tree)
{
    struct stat		stats;
    int			fk;
    int			fd;

    //proteger fork
    if (stat(tree->right->data[0], &stats) == 0)
    {
	if (stats.st_mode & S_IFDIR)
	{
	    ft_printf_fd(2, "vsh: is a directory: %s\n", tree->right->data[0]);
	    return ;
	}
    }
    if ((fd = open(tree->right->data[0], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
    {
	perror("vsh");
	return ;
    }
    fk = fork();
    if (fk == 0)
    {
	dup2(fd, 1);
	close(fd);
	exec_commands(tree->left);
	exit(0);
    }
    else if (fk > 0)
	wait(NULL);
}

static void		double_right_redirection(t_tree *tree)
{
    struct stat		stats;
    int			fk;
    int			fd;

    //proteger fork
    if (stat(tree->right->data[0], &stats) == 0)
    {
	if (stats.st_mode & S_IFDIR)
	{
	    ft_printf_fd(2, "vsh: is a directory: %s\n", tree->right->data[0]);
	    return ;
	}
    }
    if ((fd = open(tree->right->data[0], O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
    {
	perror("vsh");
	return ;
    }
    fk = fork();
    if (fk == 0)
    {
	dup2(fd, 1);
	close(fd);
	exec_commands(tree->left);
	exit(0);
    }
    else if (fk > 0)
	wait(NULL);
}

static void		left_redirection(t_tree *tree)
{
    struct stat		stats;
    int			fk;
    int			fd;

    //proteger fork
    if (stat(tree->right->data[0], &stats) == 0)
    {
	if (!(stats.st_mode & S_IRUSR))
	{
	    ft_printf_fd(2, "vsh: permission denied: %s\n", tree->right->data[0]);
	    return ;
	}
    }
    if ((fd = open(tree->right->data[0], O_RDONLY)) < 0)
    {
	perror("vsh");
	return ;
    }
    fk = fork();
    if (fk == 0)
    {
	dup2(fd, 0);
	close(fd);
	exec_commands(tree->left);
	exit(0);
    }
    else if (fk > 0)
	wait(NULL);
}

void		redirection(t_tree *tree)
{
    if (tree->type == right_redir)
	right_redirection(tree);
    if (tree->type == double_right_redir)
	double_right_redirection(tree);
    if (tree->type == left_redir)
	left_redirection(tree);
}
