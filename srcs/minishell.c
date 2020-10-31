#include "builtins.h"
#include "tree.h"

int main(int v, char **n, char **envp)
{
	int	i;
	int	ret;
	char	*line;
	t_list	*cmd_tree_list;

	if (n != 0)
	{} //error
	display_ascii_art();
	init_env(envp);
	i = 1;
	while(n)
	{
		ft_printf("(los voltereta)-> ");
		i = gnl(0, &line);
		cmd_tree_list = parse_line(line);
		//draw_list(tree_list);
		//do whatever with line
		ret = exec_commands(cmd_tree_list);
		free(line);
	}
	return (0);
}
