#include "builtins.h"
#include "tree.h"

int		exec_commands(t_tree *tree)
{
	t_tree *root;
	int	ret;

	root = tree;
	if (!tree || !(tree->data[0]))
		return (0);
	if (tree->left != NULL)
		ret = exec_commands(tree->left);
	if (tree->data[0][0] != '|' && tree->data[0][0] != '>' && tree->data[0][0] != '<')
		ret = function(tree->data);
	else if (tree->right)
		ret = function(tree->right->data);
	return (ret);
}
