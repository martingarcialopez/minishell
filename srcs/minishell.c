#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include <setjmp.h>
#include <sys/wait.h>

static jmp_buf env;
void	shell_loop(void);

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
	t_list	*cmd_tree_list;
	
	while(1)
	{
		ft_printf("(los voltereta)-> ");
		i = gnl(0, &line);
		if (!i)
		{
			ft_printf("exit\n");
			exit(2);
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
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ret = 0;
	while (!ret)
		ret = fork_shell_loop();
	return (0);
}
