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

int		    exec_single_command(char *line)
{
	int	ret;
	char	sep;
	t_list	*tkn_lst;
	t_list	*tmp;
	t_tree	*cmd_tree;

	    tkn_lst = pparse_line(line);
	    tmp = tkn_lst;
	    while (tkn_lst)
	    {
	    	sep = 0;
	    	cmd_tree = bbuild_tree(&tkn_lst, &sep);
//	    	print_ascii_tree(cmd_tree);
	    	ret = exec_commands(cmd_tree);
	    	save_return(ret);
	    	if (((sep == '&' && ret != 0) || (sep == '|' && ret == 0)))
	    		break;
	    	if (tkn_lst)
	    		tkn_lst = tkn_lst->next;
	    	free_tree(cmd_tree);
	    }
	    ft_lstclear(&tmp, &free_token);
	    return (g_ret);
}

int		    main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	if (ac > 1)
	{
	    if (ac >= 2 && ft_strcmp(av[1], "-c") == 0)
	    {
		if (ac == 2)
		{
		    ft_printf_fd(2, "%s: -c: option requires an argument\n", g_data[ARGV0]);
		    exit(1);
		}
		init_env(envp);
		init_data(av);
		return (exec_single_command(av[2]));
	    }
	}
	init_env(envp);
	init_data(av);
	display_ascii_art();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	prompt_loop();
	exit(0);
	return (0);
}
