/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:23:31 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/01 13:57:51 by mgarcia-         ###   ########.fr       */
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
		{
			root->left = new;
			return (1);
		}
		return (0);
	}
	if (ft_add_leaf_dfs(&(root->left), new))
		return (1);
	if (root && root->right == NULL)
	{
		if (type == pipeline || type == right_redir ||
			type == left_redir || type == double_right_redir)
		{
			root->right = new;
			return (1);
		}
		return (0);
	}
	return (0);
}

void			print_dfs_tree(t_tree *node)
{
	if (!node)
		return ;
	ft_printf("type-> %d, val-> %s\n", node->type, node->data[0]);
	print_dfs_tree(node->left);
	print_dfs_tree(node->right);
}
