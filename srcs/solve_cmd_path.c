#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include "unistd.h"
#include <sys/wait.h>
#include <sys/stat.h>


char			*solve_abs_path(char **args)
{
	struct stat	stats;
	
	stat(args[0], &stats);
	//if (stats.st_mode & S_IXUSR)
	return (args[0]);
	
}

char			*solve_relative_path(char **args)
{
	struct stat	stats;
	char		*path;
	char		*abs_path;
	int		len;

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
	//stats
	return (abs_path);
}

char			*find_path(char **args)
{
	struct stat	stats;
	char		*path;
	char		*abs_path;
	char		**split_path;
	int		len;
	int		i;
	
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

char			*solve_cmd_path(char **args)
{
	if (args[0][0] == '/')
		return (solve_abs_path(args));
	else if (args[0][0] == '.')
		return (solve_relative_path(args));
	else
		return (find_path(args));	
}
