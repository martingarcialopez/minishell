#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include <setjmp.h>
#include <sys/wait.h>

static jmp_buf env;
void	shell_loop(void);

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
	char	sep;
	t_list	*tkn_lst;
	t_list	*tmp;
	t_token	*token;
	t_tree	*cmd_tree;

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

		tkn_lst = pparse_line(line);

/*		tmp = tkn_lst;
		while (tkn_lst)
		{
			token = (t_token*)(tkn_lst->content);
			ft_printf("%s <- %d\n", token->value, token->type);
			tkn_lst = tkn_lst->next;
		}

		tkn_lst = tmp;
*/
		free(line);


		cmd_tree = bbuild_tree(&tkn_lst, &sep);
	//	print_ascii_tree(cmd_tree);
		ret = exec_commands(cmd_tree);
		save_return(ret);


/*		cmd_tree_list = parse_line(line);
		//draw_list(cmd_tree_list);
		while (cmd_tree_list)
		{
			ret = exec_commands((t_tree*)(cmd_tree_list->content));
			cmd_tree_list = cmd_tree_list->next;
			// Implementar && y || dependiendo del ret
		}
		save_return(ret);
		free(line);*/
	}
}


/* 
void	signal_handler(int sigid)
{
	ft_printf("\n");
	shell_loop();
}

void		shell_loop(void)
{
	int	i;
	int	ret;
	char	*line;
	char	sep;
	//t_list	*cmd_tree_list;
	t_list	*tkn_lst;

	t_list	*tmp;
	t_token	*token;

	t_tree	*cmd_tree;
	
	while(1)
	{
		ft_printf("(los voltereta)-> ");
		i = gnl(0, &line);
		if (!i)
		{
			ft_printf("exit\n");
			exit(2);
		}

		tkn_lst = pparse_line(line);

		tmp = tkn_lst;
		while (tkn_lst)
		{
			token = (t_token*)(tkn_lst->content);
			ft_printf("%s <- %d\n", token->value, token->type);
			tkn_lst = tkn_lst->next;
		}

		tkn_lst = tmp;

		free(line);


		cmd_tree = bbuild_tree(&tkn_lst, &sep);
	//	print_ascii_tree(cmd_tree);
		ret = exec_commands(cmd_tree);
		save_return(ret);

*/
/*	
		sep = ';';
		while (tkn_lst)
		{
			cmd_tree = bbuild_tree(&tkn_lst, &sep);
			ft_printf("Holaaaaasafsdfasa\n");
			//ft_printf("\n\nprintf_ascii_tree : -> \n");
			//print_ascii_tree(cmd_tree);	
			ft_printf("que conno");
			//print_dfs_tree(cmd_tree);
			ft_printf("te pasa\n");
			ret = exec_commands(cmd_tree);
			save_return(ret);
			if ((sep == '&' && ret != 0) || (sep == '|' && ret == 0))
				break;
		//	tkn_lst = tkn_lst->next;
		}
*/	
/*		cmd_tree_list = parse_line(line);
		draw_list(cmd_tree_list);
		while (cmd_tree_list)
		{
			ret = exec_commands((t_tree*)(cmd_tree_list->content));
			cmd_tree_list = cmd_tree_list->next;
			// Implementar && y || dependiendo del ret
		}
		save_return(ret);
		free(line);*/
/*	}
	
}

int		fork_shell_loop()
{
	int	pid;	
	int	status;

	//secure fork
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		shell_loop();
	}	
	else if (pid > 0)
	{
		wait(&status);
		if (WIFSIGNALED(status))
		{
			ft_printf("\n");
			return (0);
		}
		return (1);	
	}
	return (0);
}

int main(int v, char **n, char **envp)
{
	int	pid;
	int	ret;	

	if (n != 0)
	{} //error
	display_ascii_art();
	init_env(envp);
	init_data();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ret = 0;
	while (!ret)
		ret = fork_shell_loop();
	return (0);
}*/
