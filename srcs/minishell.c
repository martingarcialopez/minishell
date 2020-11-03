#include "builtins.h"
#include "tree.h"
#include "libft.h"

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
		while (cmd_tree_list)
		{
			ret = exec_commands((t_tree*)(cmd_tree_list->content));
			cmd_tree_list = cmd_tree_list->next;
			// Implementar && y || dependiendo del ret
		}
		//draw_list(cmd_tree_list);
		//do whatever with line
		//ret = function(((t_tree*)(cmd_tree_list->content))->data);
		free(line);
	}
	return (0);
}
