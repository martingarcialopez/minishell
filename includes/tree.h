/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:21:56 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/11/06 16:53:21 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TREE_H_
# define _TREE_H_

#include "libft.h"
#include <sys/wait.h>

typedef struct		s_tree
{
	char		**data;
	struct s_tree	*left;
	struct s_tree	*right;
}			t_tree;


t_tree			*ft_newtree(char **content);

void			ft_treeadd_root(t_tree **rtree, t_tree *new);

int			ft_add_leaf_dfs(t_tree **rtree, t_tree *new);

void			print_dfs_tree(t_tree *node);

void			print_ascii_tree(t_tree *t);

void			draw_list(t_list *list);

t_list			*parse_line(char *str);

void			display_ascii_art(void);

int			exec_commands(t_tree *tree);

int			call_system_function(char **args);

char			**env_to_vect(void);

int			retrieve_env_variable(char *name, char **value);

char			*solve_cmd_path(char **args);

void			redirection(t_tree *tree);

#endif
