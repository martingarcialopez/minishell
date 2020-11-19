#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int	call_system_function(char **args)
{
	char	**env;
	char	*abs_path;
	int	fk;
	int	status;

	abs_path = solve_cmd_path(args);
	env = env_to_vect();
	fk = fork();	
	if (fk == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (!(execve(abs_path, args, env)))
			perror("vsh");
		free_tab(env);
		exit(1);
	}
	else if (fk > 0)
	{
		signal(SIGINT, SIG_IGN);
		free(abs_path);
		wait(&status);
		signal(SIGINT, &signal_handler);
		free_tab(env);
		if (WIFSIGNALED(status))
			ft_printf("\n");
		if (WIFEXITED(status)) 
        		return (status); 
	}
	else
	{
		free_tab(env);
		ft_printf("Error: fork not working\n");
		return (1);
	}
	return (1);
}
