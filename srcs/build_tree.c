/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:59:22 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/01 11:23:32 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"

char				**create_command(t_list **alst, t_list *lst)
{
	t_list	*begin;
	t_token	*token;
	char	**cmd;
	int		i;

	begin = *alst;
	i = 1;
	while (begin != lst)
	{
		i++;
		begin = begin->next;
	}
	cmd = (char**)sec(malloc(sizeof(char*) * (i + 1)));
	while (--i > 0)
		cmd[i] = NULL;
	begin = *alst;
	while (begin != lst)
	{
		token = begin->content;
		if (token->type == literal)
			cmd[i++] = sec(ft_strdup(token->value));
		begin = begin->next;
	}
	cmd[++i] = NULL;
	return (cmd);
}

void				create_operator_node(t_token *token, t_tree **root)
{
	t_tree	*tree;
	char	**cmd;

	cmd = (char**)sec(malloc(sizeof(char*) * 1));
	cmd[0] = NULL;
	tree = ft_newtree(token->type, cmd);
	ft_treeadd_root(root, tree);
}

void				create_literal_node(t_tree **root, t_list *lst,
															t_list **alst)
{
	t_tree	*tree;
	char	**cmd;

	if (*alst != lst)
	{
		cmd = create_command(alst, lst);
		tree = ft_newtree(literal, cmd);
		if (!(*root))
			ft_treeadd_root(root, tree);
		else
			ft_add_leaf_dfs(root, tree);
	}
	if (lst)
		*alst = lst->next;
}

t_tree				*bbuild_tree(t_list *lst)
{
	t_list		*alst;
	t_token		*token;
	t_tree		*root;

	alst = lst;
	root = NULL;
	while (lst)
	{
		token = (t_token*)(lst->content);
		if ((token->type == pipeline) || (token->type == right_redir)
		|| (token->type == left_redir) || (token->type == double_right_redir))
		{
			create_operator_node(token, &root);
			create_literal_node(&root, lst, &alst);
		}
		lst = lst->next;
	}
	create_literal_node(&root, lst, &alst);
	return (root);
}
