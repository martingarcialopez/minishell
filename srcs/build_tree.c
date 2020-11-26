/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:59:22 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/11/25 19:18:16 by mgarcia-         ###   ########.fr       */
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

t_tree				*bbuild_tree(t_list **alst)
{
	t_list		*lst;
	t_token		*token;
	t_tree		*root;
	t_tree		*tree;
	char		**cmd;

	root = NULL;
	lst = *alst;
	while (lst)
	{
		token = (t_token*)(lst->content);
		if ((token->type == pipeline) || (token->type == right_redir)
				|| (token->type == left_redir)
				|| (token->type == double_right_redir))
		{
			cmd = (char**)sec(malloc(sizeof(char*) * 2));
			cmd[0] = sec(ft_strdup("op"));
			cmd[1] = NULL;
			tree = ft_newtree(token->type, cmd);
			ft_treeadd_root(&root, tree);
			cmd = create_command(alst, lst);
			tree = ft_newtree(literal, cmd);
			ft_add_leaf_dfs(&root, tree);
			*alst = lst->next;
		}
		lst = lst->next;
	}
	cmd = create_command(alst, lst);
	tree = ft_newtree(literal, cmd);
	if (!root)
		ft_treeadd_root(&root, tree);
	else
		ft_add_leaf_dfs(&root, tree);
	return (root);
}
