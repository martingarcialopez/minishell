/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:23:31 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/02 09:12:37 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "libft.h"
#include "builtins.h"

void			free_tree(t_tree *node)
{
	if (!node)
		return ;
	if (node->left)
		free_tree(node->left);
	if (node->right)
		free_tree(node->right);
	free_tab(node->data);
	free(node);
}

t_tree			*ft_newtree(t_token_type type, char **cmd)
{
	t_tree	*new;

	if (!(new = (t_tree*)sec(malloc(sizeof(t_tree)))))
		return (NULL);
	new->type = type;
	new->data = cmd;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void			ft_treeadd_root(t_tree **rtree, t_tree *new)
{
	t_tree	*root;

	root = *rtree;
	if (!root)
		*rtree = new;
	else
	{
		new->left = root;
		*rtree = new;
	}
}

int				add_new_to_node(t_tree *new, t_tree **node)
{
	*node = new;
	return (1);
}

int				ft_add_leaf_dfs(t_tree **rtree, t_tree *new)
{
	t_tree			*root;
	t_token_type	type;

	root = *rtree;
	type = root->type;
	if (root && root->left == NULL)
	{
		if (type == pipeline || type == right_redir
			|| type == left_redir || type == double_right_redir)
			return (add_new_to_node(new, &(root->left)));
		return (0);
	}
	if (ft_add_leaf_dfs(&(root->left), new))
		return (1);
	if (root && root->right == NULL)
	{
		if (type == pipeline || type == right_redir ||
			type == left_redir || type == double_right_redir)
			return (add_new_to_node(new, &(root->right)));
		return (0);
	}
	return (0);
}
