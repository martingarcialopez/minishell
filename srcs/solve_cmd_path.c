#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include "unistd.h"
#include <sys/wait.h>
#include <sys/stat.h>

#ifndef _DARWIN_FEATURE_64_BIT_INODE
# define _DARWIN_FEATURE_64_BIT_INODE
#endif

char			*solve_abs_path(char **args)
{
	char		*abs_path;
	
	abs_path = sec(ft_strdup(args[0]));
	return (abs_path);
	}

char			*solve_home(char *arg)
{
	char		*path;
	char		*abs_path;
	int		len;

	if (!(retrieve_env_variable("HOME", &path)))
	    return (error_retrieving_env_variable("HOME"));
	len = ft_strlen(path) + ft_strlen(arg) + 1;
	abs_path = (char*)sec(malloc(sizeof(char) * len));
	abs_path[0] = '\0';
	ft_strcat(abs_path, path);
	ft_strcat(abs_path, ++arg);
	free(path);
	return (abs_path);
}

char			*solve_relative_path(char **args)
{
	struct stat	stats;
	char		*path;
	char		*abs_path;
	int		len;

	if (!(retrieve_env_variable("PWD", &path)))
	    return (error_retrieving_env_variable("PWD"));	
	len = ft_strlen(path) + ft_strlen(args[0]) + 1;
	abs_path = (char*)sec(malloc(sizeof(char) * len));
	abs_path[0] = '\0';
	ft_strcat(abs_path, path);
	ft_strcat(abs_path, (*args + 1));
	stat(abs_path, &stats);	
	//stats
	free(path);
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
	    return (error_retrieving_env_variable("PATH"));
	len = ft_strlen(path) + ft_strlen(args[0]) + 1;
	abs_path = (char*)sec(malloc(sizeof(char) * len));
	split_path = sec(ft_split(path, ':'));
	free(path);
	i = 0;
	while (split_path[i])
	{
		abs_path[0] = '\0';
		ft_strcat(abs_path, split_path[i]);
		ft_strcat(abs_path, "/");
		ft_strcat(abs_path, args[0]);
		if (stat(abs_path, &stats) == 0)
		{
			if (stats.st_mode & S_IXUSR)
			{
				free_tab(split_path);	
				return (abs_path);
			}
		}
		i++;
	}
        ft_printf_fd(2, "vsh: command not found: %s\n", args[0]);
	free_tab(split_path);
	free(abs_path);
	return (NULL);
}

char			*solve_cmd_path(char **args)
{
	if (args[0][0] == '/')
		return (solve_abs_path(args));
	else if (args[0][0] == '.')
		return (solve_relative_path(args));
	else if (args[0][0] == '~')
		return (solve_home(args[0]));
	else
		return (find_path(args));	
}
