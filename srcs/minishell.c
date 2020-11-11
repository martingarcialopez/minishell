#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include <setjmp.h>

static jmp_buf env;

void	signal_handler(int sigid)
{
	if (sigid == SIGINT)
		longjmp(env, 42);
}

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
	init_data();
	i = 1;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while(1)
	{
		if (setjmp(env) == 42)
		{
			ft_printf("\n");
			continue ;
		}
		ft_printf("(los voltereta)-> ");
		i = gnl(0, &line);
		if (!i)
		{
			ft_printf("exit\n");
			exit(0);
		}
		cmd_tree_list = parse_line(line);
		//draw_list(cmd_tree_list);
		while (cmd_tree_list)
		{
			ret = exec_commands((t_tree*)(cmd_tree_list->content));
			cmd_tree_list = cmd_tree_list->next;
			// Implementar && y || dependiendo del ret
		}
		save_return(ret);
		free(line);
	}
	return (0);
}
