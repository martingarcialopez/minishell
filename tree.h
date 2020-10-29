/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:21:56 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/10/29 16:05:08 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TREE_H_
# define _TREE_H_

#include "libft.h"

typedef struct		s_tree
{
	char			**data;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

t_tree			*ft_newtree(char **content);

void			ft_treeadd_root(t_tree **rtree, t_tree *new);

int				ft_add_leaf_dfs(t_tree **rtree, t_tree *new);

void			print_dfs_tree(t_tree *node);

void			print_ascii_tree(t_tree *t);

void			draw_list(t_list *list);

#endif
