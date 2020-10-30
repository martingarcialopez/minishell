#include "builtins.h"
#include "tree.h"

int main(int v, char **n, char **envp)
{
	int	i;
	char	*line;
	t_list	*tree_list;

	if (n != 0)
	{} //error
	
	ft_printf("***************************************************************\n");
	ft_printf("*                                                             *\n");
	ft_printf("*                                             _ _       \\ \\   *\n");
	ft_printf("*      --    MINISHELL v0.0  --    .-\"\"\"\"\"-. / \\_> /\\    |/   *\n");
	ft_printf("*                                 /         \\.'`  `',.--//    *\n");
	ft_printf("*                               -(    Y2K    I      I  @@\\    *\n");
	ft_printf("*   The only bug in our code ->   \\         /'.____.'\\___|    *\n");
	ft_printf("*                                  '-.....-' __/ | \\   (`)    *\n");
	ft_printf("*                                           /   /  /          *\n");
	ft_printf("*      by mgarcia- & daprovin                    \\  \\         *\n");
	ft_printf("*                                                             *\n");
	ft_printf("***************************************************************\n");

	init_env(envp);
	i = 1;
	while(n)
	{
		ft_printf("(los voltereta)-> ");
		i = gnl(0, &line);
		tree_list = parse_line(line);
		draw_list(tree_list);
		//do whatever with line
		free(line);
	}
	return (0);
}
