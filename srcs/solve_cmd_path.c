#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include "unistd.h"
#include <sys/wait.h>
#include <sys/stat.h>

char			*command_not_found(char **tab, char *str, char *cmd)
{
	free_tab(tab);
	free(str);
	ft_printf_fd(2, "%s: %s: command not found\n", g_data[ARGV0], cmd);
	return (NULL);
}

char			*free_tab_and_return_path(char **tab, char *abs_path)
{
    free_tab(tab);
    return (abs_path);
}

int			check_path_status(char *path)
{
    struct stat		stats;

    if (stat(path, &stats) == 0)
    {
//	if (stats.st_mode & S_IXUSR)
	    return (0);
//	return (1);
    }
    return (2);
}

char			*solve_abs_path(char **args)
{
//	int		errnum;
	char		*abs_path;

	abs_path = sec(ft_strdup(args[0]));
/*	if ((errnum = check_path_status(abs_path)) == 0)
	    return (abs_path);
	//free(abs_path);
	return (path_error(errnum, abs_path));*/
	return (abs_path);
}

char			*solve_home(char *arg)
{
//	int		errnum;
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
/*	if ((errnum = check_path_status(abs_path)) == 0)
	    return (abs_path);
	free(abs_path);
	return (path_error(errnum, arg));*/
	return (abs_path);
}

char			*solve_relative_path(char **args)
{
//	int		errnum;
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
	free(path);
/*	if ((errnum = check_path_status(abs_path)) == 0)
	    return (abs_path);
	free(abs_path);
	return (path_error(errnum, args[0]));*/
	return (abs_path);
}

char			*find_path(char **args)
{
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
		if (check_path_status(abs_path) == 0)
		    return (free_tab_and_return_path(split_path, abs_path));
		i++;
	}
	return (command_not_found(split_path, abs_path, args[0]));
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
