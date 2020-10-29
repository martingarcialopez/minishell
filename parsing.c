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
	char			**data;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

void		print_ascii_tree(t_tree *t);

t_tree			*ft_newtree(char **content)
{
	t_tree	*new;

	if (!(new = (t_tree*)malloc(sizeof(t_tree))))
		return (NULL);
	new->data = content;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void			ft_treeadd_root(t_tree **rtree, t_tree *new)
{
	t_tree	*root;

	root = *rtree;
	if (!root)
		*rtree = (new);
	new->left = root;
	*rtree = new;
}

int				ft_add_leaf_dfs(t_tree **rtree, t_tree *new)
{
	t_tree *root;

	root = *rtree;
	if (root && root->left == NULL)
	{
		if (root->data[0][0] == '|' || root->data[0][0] == '>' || root->data[0][0] == '<')
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
		if (root->data[0][0] == '|' || root->data[0][0] == '>' || root->data[0][0] == '<')
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
	ft_printf("%s  --  ", node->data);
	print_dfs_tree(node->left);
	print_dfs_tree(node->right);
}


/*
1 buscar el ;
2 buscar operadores
3 si los hay, todas las palabras anteriores como leftmost depthmost operand
4 si no, todo hasta el ; es root, unico nodo del arbol
5 avanzar desde el operador y repetir el proceso
*/

	//tree_list = parse_line(" env |  wc -l | bc > toto");

t_tree				*build_tree(char **words, int semicolon)
{
	t_tree		*root;
	t_tree		*tree;
	char		**cmd;
	int			i;
	int			j;
	int			k;
	int			last_semicolon;
	i = 0;

	root = NULL;
	last_semicolon = 0;
	//ft_printf ("on call semicolon is %d and words is :\n", semicolon);
	//while (words[i])
	//	ft_printf("%s ", words[i++]);
	//ft_printf("\n\n");

	
	i = 0;
	j = 0;
	while (i < semicolon)
	{
		if (words[i][0] == '|' || words[i][0] == '>' || words[i][0] == '<' )
		{

			cmd = (char**)malloc(sizeof(char*) * 2);
			cmd[0] = ft_strdup(words[i]);
			cmd[1] = NULL;

			last_semicolon = i;
			tree = ft_newtree(cmd);
			ft_treeadd_root(&root, tree);

			// super join 
			
			//proteger malloc de la siguente linea

			k = 0;
			cmd = (char**)malloc(sizeof(char*) * (i - j + 1));
			while (j < i)
				cmd[k++] = ft_strdup(words[j++]);
			cmd[k] = NULL;
			j++;


			tree = ft_newtree(cmd);
			ft_add_leaf_dfs(&root, tree);

			ft_printf("\n\n");
		}
		i++;
	}
	k = 0;
	cmd = (char**)malloc(sizeof(char*) * (i - j + 1));
	while (j < i)
	{
		cmd[k++] = words[j];
		j++;
	}
	cmd[k] = NULL;


	tree = ft_newtree(cmd);
	if (!root)
		ft_treeadd_root(&root, tree);
	else
		ft_add_leaf_dfs(&root, tree);
	//print_dfs_tree(root);
	//print_ascii_tree(root);
	return (root);
}


t_list				*parse_line(char *str)
{
	t_list	*tree_list;
	t_list	*list;
	char	**words;
	int		i;
	
	i = 0;
	tree_list = NULL;
	//TO_DO: aislar separadores y comandos que no esten rodeados de espacios
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
	t_list	*alst;
	int i;

	alst = list;
	i = 1;
	ft_printf("o-> ");
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


int main(int ac, char **av)
{
	t_list *tree_list;

//	tree_list = parse_line(" env | wc -l | bc > toto ");
	
	tree_list = parse_line(av[1]);
	
	ft_printf("\n\n");
	draw_list(tree_list);
	
	return (0);
}
