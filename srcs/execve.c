#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>


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
		if (!(execve(abs_path, args, env)))
			perror("vsh");
		return (1);
	}
	else if (fk > 0)
	{
		wait(&status);
		if (WIFEXITED(status)) 
        		return (status); 
	}
	else
	{
		ft_printf("Error: fork not working\n");
		return (1);
	}
	return (1);
}