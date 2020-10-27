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

/*
1 buscar el ;
2 buscar operadores
3 si los hay, todas las palabras anteriores como leftmost depthmost operand
4 si no, todo hasta el ; es root, unico nodo del arbol
5 avanzar desde el operador y repetir el proceso
*/


t_list				*build_tree(char **words, int semicolon)
{
	int		i;
	
	t_list *test = NULL;

	return (test);
}

t_list				*parse_line(char *str)
{
	t_list	*tree_list;
	t_list	*list;
	char	**words;
	int		i;
	
	tree_list = NULL;
	words = ft_split(str, 32);
	while (words[i])
	{
		if (words[i][0] && words[i][0] == ';')
		{
			list = ft_lstnew((void*)build_tree(words, i));
			ft_lstadd_back(&tree_list, list);
		}
		i++;
	}
	if (!tree_list)
	{
		list = ft_lstnew((void*)build_tree(words, i));
		ft_lstadd_back(&tree_list, list);
	}
	return (tree_list);
}


void			draw_list(t_list *list)
{
	int i;

	i = 1;
	ft_printf("o-> ");
	while (list)
	{
		ft_printf("node%d ----> ", i++);
		list = list->next;		
	}
	ft_printf("NULL\n");
}


int main(int ac, char **av)
{
	t_list *tree_list;

	tree_list = parse_line("env | wc -l | wc > toto");
	
	draw_list(tree_list);
	
	return (0);
}
