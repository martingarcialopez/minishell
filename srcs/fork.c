#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include "unistd.h"
#include "sys/wait.h"

char	*create_abs_path(char **args)
{
	char	*abs_path;
	char	*bin;
	int	len;

	bin = "/bin/";
	len = ft_strlen(bin) + ft_strlen(args[0]) + 1;
	abs_path = (char*)malloc(sizeof(char) * len);
	abs_path[0] = '\0';
	ft_strcat(abs_path, bin);
	ft_strcat(abs_path, args[0]);
	return (abs_path);	
}

int	call_system_function(char **args)
{
	char	**env;
	char	*abs_path;
	int	fk;
	int	status;

	abs_path = create_abs_path(args);
	env = env_to_vect();
	fk = fork();	
	if (fk == 0)
	{
		execve(abs_path, args, env);
		ft_printf("Error: command not found\n");
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
