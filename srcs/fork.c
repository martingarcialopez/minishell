#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include "unistd.h"
#include <sys/wait.h>
#include <sys/stat.h>

int	retrieve_env_variable(char *name, char **value)
{
	t_env		*list;
	
	list = g_env;
	while (list)
	{
		if (ft_strcmp(list->name, name) == 0)
		{
			*value = list->value;
			return(1);
		}
		list = list->next;	
	}	
	return (0);	
}

char	*create_abs_path(char **args)
{
	struct stat	stats;
	char		*path;
	char		*abs_path;
	char		**split_path;
	int		len;
	int		i;

	if (args[0][0] == '/')
	{
		stat(args[0], &stats);
		if (stats.st_mode & S_IXUSR)
			return (args[0]);
	}
	else if (args[0][0] == '.')
	{
		if (!(retrieve_env_variable("PWD", &path)))
		{
			ft_printf("Error: PWD variable not found in env\n");
			return (NULL);
		}
		len = ft_strlen(path) + ft_strlen(args[0]) + 1;
		abs_path = (char*)malloc(sizeof(char) * len);
		abs_path[0] = '\0';
		ft_strcat(abs_path, path);
		ft_strcat(abs_path, ++args[0]);
		stat(abs_path, &stats);	
		if (stats.st_mode & S_IXUSR)
			return (abs_path);
		else
		{
			ft_printf("Shell: Permission denied\n");
			return (NULL);
		}
	}

	if (!(retrieve_env_variable("PATH", &path)))
	{
		ft_printf("Error: PATH variable not found in env\n");
		return (NULL);
	}
	len = ft_strlen(path) + ft_strlen(args[0]) + 1;
	abs_path = (char*)malloc(sizeof(char) * len);
	split_path = ft_split(path, ':');
	i = 0;
	while (split_path[i])
	{
		abs_path[0] = '\0';
		ft_strcat(abs_path, split_path[i]);
		ft_strcat(abs_path, "/");
		ft_strcat(abs_path, args[0]);
		stat(abs_path, &stats);
		if (stats.st_mode & S_IXUSR)
			return (abs_path);
		i++;
	}
	ft_printf("Error: Command not found in PATH\n");
	return (NULL);
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
