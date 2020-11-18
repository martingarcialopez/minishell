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
		free(abs_path);
		wait(&status);
		free_tab(env);
		if (WIFSIGNALED(status))
			kill(fk, SIGINT);
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
