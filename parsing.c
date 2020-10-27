#include <unistd.h>
#include <stdio.h>
#include "libft.h"

/*
typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;
*/

typedef struct		s_tree
{
	char			token;
	char			*data;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

t_tree			*ft_newtree(char *content)
{
	t_tree	*new;

	if (!(new = (t_tree*)malloc(sizeof(t_tree))))
		return (NULL);
	new->data = content;
	new->left = NULL;
	new->right = NULL;
}

t_tree			*ft_treeadd_root(t_tree *rtree, t_tree *new)
{
	if (!rtree)
		return (new);
	new->left = rtree;
	return (new);
}

t_tree			*ft_add_leaf_dfs(t_tree *root, t_tree *new)
{
	if (root->left = NULL)
	{
		root->left = new;
		return (root);
	}
	else
		root = ft_add_leaf_dfs(root->left, new);
	if (
		
}

/*
1 buscar el ;
2 buscar operadores
3 si los hay, todas las palabras anteriores como leftmost depthmost operand
4 si no, todo hasta el ; es root, unico nodo del arbol
5 avanzar desde el operador y repetir el proceso
*/

	//tree_list = parse_line(" env |  wc -l |   wc > toto");

t_tree				*build_tree(char **words, int semicolon)
{
	t_tree		*root;
	t_tree		*tree;
	int		i;
	i = 0;

	root = NULL;
	ft_printf ("on call semicolon is %d and words is :\n", semicolon);
	while (words[i])
		ft_printf("%s ", words[i++]);
	ft_printf("\n\n");


	
	i = 0;
	

	while (i < semicolon)
	{
		if (words[i] == '|' || words[i] == '>' || words[i] == '<' )
		{
			//anadir, crear root
			//todo lo anterior al index del operador on the leftmost deepmost		
			tree = ft_newtree(words[i]);
			root = ft_treeadd_root(root, tree);

			tree = ft_newtree(words[i - 1]);
			root = ft_add_leaf_dfs(root, tree);
			
		}
		i++;
	}
	if (ni un puto operador pisha
		aka if !tree
	crear root, todo dentro



t_list *test = NULL;	
	return (test);
	
}

t_list				*parse_line(char *str)
{
	t_list	*tree_list;
	t_list	*list;
	char	**words;
	int		i;
	
	i = 0;
	tree_list = NULL;
	words = ft_split(str, 32);
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


void			draw_list(t_list *list)
{
	int i;

	i = 1;
	ft_printf("o-> ");
	while (list)
	{
		ft_printf("node%d ---> ", i++);
		list = list->next;		
	}
	ft_printf("NULL\n");
}


int main(int ac, char **av)
{
	t_list *tree_list;

	tree_list = parse_line(" env |  wc |   wc > toto");
	
	draw_list(tree_list);
	
	return (0);
}
