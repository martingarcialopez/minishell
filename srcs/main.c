#include "libft.h"
#include "tree.h"

int main(int ac, char **av)
{
	t_list	*tree_list;

	if (av[1])
		tree_list = parse_line(av[1]);

	draw_list(tree_list);
	
	return (0);
}
