/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:23:31 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/10/29 16:05:07 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "libft.h"

t_tree			*ft_newtree(t_token_type type, char **cmd)
{
	t_tree	*new;

	if (!(new = (t_tree*)malloc(sizeof(t_tree))))
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
		new->left = root;
		*rtree = new;
}

int				ft_add_leaf_dfs(t_tree **rtree, t_tree *new)
{
	t_tree		*root;
	t_token_type	type;

	root = *rtree;
	type = root->type;	
	if (root && root->left == NULL)
	{
		if (type == pipeline || type == right_redir || type == left_redir || type == double_right_redir)
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
		if (type == pipeline || type == right_redir || type == left_redir || type == double_right_redir)
		{
			root->right = new;
			return (1);	
		}
		return (0);
	}
	return (0);
}

void		print_dfs_tree(t_tree *node)
{
	if (!node)
		return ;
	ft_printf("type-> %d, val-> %s\n", node->type, node->data[0]);
	print_dfs_tree(node->left);
	print_dfs_tree(node->right);
}
/*
void			draw_list(t_list *list)
{
	t_list	*alst;
	int i;

	alst = list;
	i = 1;
	ft_printf("\n\no-> ");
	while (list)
	{
		ft_printf("NODE%d ---> ", i++);
		list = list->next;		
	}
	ft_printf("NULL\n");
	ft_printf("\n\n");
	
	list = alst;
	i = 1;
	while (list)
	{
		ft_printf("NODE%d TREE:\n", i++);
		print_ascii_tree((t_tree*)list->content);
		ft_printf("\n\n");
		list = list->next;
	}
}
*/
