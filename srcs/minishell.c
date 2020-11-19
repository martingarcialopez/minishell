#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include <setjmp.h>
#include <sys/wait.h>
#include <signal.h>

void	signal_handler(int sigid)
{
	if (sigid == SIGINT)
	{
	/*	if (g_data[CHILD_RUNNING])
			ft_printf("\n") ;*/
//		else
			ft_printf("\n(los voltereta)-> ");
	}
}

void	prompt_loop()
{
	int	i;
	int	ret;
	char 	*line;
	char	sep;
	t_list	*tkn_lst;
	t_list	*tmp;
	t_tree	*cmd_tree;

	while(1)
	{
		ft_printf("(los voltereta)-> ");
		i = gnl(0, &line);
		if (!i)
		{
			ft_printf("exit\n");
			exit(0);
		}
		tkn_lst = pparse_line(line);
		free(line);
		tmp = tkn_lst;
		while (tkn_lst)
		{
			sep = 0;
			cmd_tree = bbuild_tree(&tkn_lst, &sep);
//			print_ascii_tree(cmd_tree);
			ret = exec_commands(cmd_tree);
			save_return(ret);
			if (((sep == '&' && ret != 0) || (sep == '|' && ret == 0)))
				break;
			if (tkn_lst)
				tkn_lst = tkn_lst->next;
			free_tree(cmd_tree);
		}
		ft_lstclear(&tmp, &free_token);
	}
	
}

int main(int ac, char **av, char **envp)
{
	display_ascii_art();
	init_env(envp);
	init_data();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	prompt_loop();
	exit(0);
	return (0);
}
