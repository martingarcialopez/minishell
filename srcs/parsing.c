/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:21:35 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/10/29 16:22:25 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tree.h"

char				**create_command(char **words, int *i, int *j)
{
	char		**cmd;
	int			k;

	k = 0;
	cmd = (char**)malloc(sizeof(char*) * (*i - *j + 1));
	while (*j < *i)
	{
		cmd[k] = ft_strdup(words[*j]);
		k++;
		(*j)++;
	}
	cmd[k] = NULL;
	(*j)++;
	return (cmd);
}

t_tree				*build_tree(char **words, int semicolon)
{
	t_tree		*root;
	t_tree		*tree;
	char		**cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	root = NULL;
	while (i < semicolon)
	{
		if (words[i][0] == '|' || words[i][0] == '>' || words[i][0] == '<' )
		{
			cmd = (char**)malloc(sizeof(char*) * 2);
			cmd[0] = ft_strdup(words[i]);
			cmd[1] = NULL;
			tree = ft_newtree(cmd);
			ft_treeadd_root(&root, tree);
			cmd = create_command(words, &i, &j);
			tree = ft_newtree(cmd);
			ft_add_leaf_dfs(&root, tree);
		}
		i++;
	}
	cmd = create_command(words, &i, &j);
	tree = ft_newtree(cmd);
	if (!root)
		ft_treeadd_root(&root, tree);
	else
		ft_add_leaf_dfs(&root, tree);
	return (root);
}

int				is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&' || c == ';')
		return (1);
	return (0);
}

char				*str_preprocessing(char *str)
{
	char	*s;
	int	len;
	int 	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (is_operator(str[i]))
			k++;
		i++;
	}
	len = ft_strlen(str) + (k * 2);
	s = (char*)malloc(sizeof(char) * len);	
	i = 0;
	while (*str)
	{
		if (!(is_operator(*str)))
			s[i++] = *str++;	
		else
		{
			s[i++] = 32;
			s[i++] = *str++;	
			if (!(is_operator(*str)))
			{
				s[i++] = 32;
				s[i++] = *str++;
			}
			else
			{
				s[i++] = *str++;
				s[i++] = 32;
			}
		}
	}
	s[i] = '\0';
	return (s);	
}

t_list				*parse_line(char *str)
{
	t_list	*tree_list;
	t_list	*list;
	char	**words;
	int	i;
	
	i = 0;
	tree_list = NULL;
	str = str_preprocessing(str);
	//ft_printf("str after preprocessing is %s\n", str);
	words = ft_split(str, 32);
	free(str);
	while (words[i])
	{
		if (words[i][0] == ';')
		{
			list = ft_lstnew((void*)build_tree(words, i));
			ft_lstadd_back(&tree_list, list);
			words = (words + i + 1);
			i = 0;
		}
		i++;
	}
	list = ft_lstnew((void*)build_tree(words, i));
	ft_lstadd_back(&tree_list, list);
	return (tree_list);
}
