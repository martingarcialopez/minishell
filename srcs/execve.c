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

	if ((abs_path = solve_cmd_path(args)) == NULL)
	    return (g_ret);
	env = env_to_vect();
	fk = fork();	
	if (fk == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(abs_path, args, env);
		//ft_printf_fd(2, "%s: %s: %s\n", g_data[ARGV0], abs_path, strerror(errno));
		exit(error(abs_path));
		//exit(127);
	}
	else if (fk > 0)
	{
		signal(SIGINT, SIG_IGN);
		free(abs_path);
		free_tab(env);
		wait(&status);
		signal(SIGINT, &signal_handler);
		if (WIFSIGNALED(status))
		{
			ft_printf("\n");
			return (status);
		}
		if (WIFEXITED(status)) 
        		return (status); 
	}
    	free_tab(env);
    	ft_printf_fd(2, "%s: error: could not fork process\n", g_data[ARGV0]);
    	return (1);
}
