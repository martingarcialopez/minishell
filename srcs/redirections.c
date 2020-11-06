#include "builtins.h"
#include "tree.h"
#include <fcntl.h>

static void		right_redirection(t_tree *tree)
{
	int	fk;
	int	fd;

	//proteger open
	//proteger fork
	fd = open(tree->right->data[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	int	fk;
	int	fd;

	//proteger open
	//proteger fork
	fd = open(tree->right->data[0], O_WRONLY | O_CREAT | O_APPEND);
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
	int	fk;
	int	fd;

	//proteger open
	//proteger fork
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
	if (ft_strcmp(tree->data[0], ">") == 0)
		right_redirection(tree);
	if (ft_strcmp(tree->data[0], ">>") == 0)
		double_right_redirection(tree);
	if (ft_strcmp(tree->data[0], "<") == 0)
		left_redirection(tree);
}
