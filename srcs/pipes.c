#include "builtins.h"
#include "tree.h"

static int		is_operator(char *str)
{
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, "||") == 0
		|| ft_strcmp(str, "&&") == 0 || ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, ">>") == 0)
		return (1);
	return (0);
}

void		pipes(t_tree *tree, int count, int backup_fd)
{
	int	fd[2];
	int	fk;
	
	pipe(fd);
	fk = fork();
	if (fk == 0)
	{
		dup2(backup_fd, 0);
		if (count)
			dup2(fd[1], 1);
		close(fd[0]);
		if (count)
			exec_commands(tree->left);
		else
			exec_commands(tree);
		exit(0);
	}
	close(fd[1]);
	if (tree->right)
		pipes(tree->right, count - 1, fd[0]);
	wait(NULL);
}

int		exec_commands(t_tree *tree)
{
	t_tree		*root;
	int		ret;

	root = tree;
	if (!tree || !(tree->data[0]))
		return (0);
	if (tree->type == right_redir || tree->type == left_redir
		|| tree->type == double_right_redir)
		redirection(tree);
	if (tree->type == pipeline)
		pipes(tree, 1, 0);
	if (tree->type == literal)
		return (function(tree->data));
	return (ret);
}
