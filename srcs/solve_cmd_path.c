#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include "unistd.h"
#include <sys/wait.h>
#include <sys/stat.h>

char			*error(int type, char *file)
{
	struct stat	stats;
	if (type == 1)
	    ft_printf_fd(2, "%s: permission denied: %s\n", g_data[ARGV0], file)
	else if (type == 2)
	    ft_printf_fd(2, "%s, no such file or directory: %s\n", g_data[ARGV0], file);
        else if (type == 0)
	    ft_printf_fd(2, "%s: command not found: %s\n", g_data[ARGV0], file);
	g_ret = 1;
	return (NULL);
}

int			check_path_status(char *path)
{
    struct stat		stats;

    if (stat(path, &stats) == 0)
    {
	if (stats.st & S_IXUSR)
	    return (0);
	return (1);
    }
    return (2);
}

char			*solve_abs_path(char **args)
{
	int		errnum;
	char		*abs_path;

	abs_path = sec(ft_strdup(args[0]));
	if ((errnum = check_path_status(abs_path)) == 0)
	    return (abs_path);
	free(abs_path);
	return (error(errnum, args[0]));
}

char			*solve_home(char *arg)
{
	int		errnum;
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
	if ((errnum = check_path_status(abs_path)) == 0)
	    return (abs_path);
	free(abs_path);
	return (error(errnum, arg));
}

char			*solve_relative_path(char **args)
{
	int		errnum;
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
	if ((errnum = check_path_status(abs_path)) == 0)
	    return (abs_path);
	free(abs_path);
	return (error(errnum, args[0]));
}

char			*find_path(char **args)
{
	int		errnum;
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
		if ((errnum = check_path_status(abs_path)) == 0)
		{
		    free_tab(split_path);
		    return (abs_path);
		}
		else if (errnum == 1)
		    break;
/*		if (stat(abs_path, &stats) == 0)
		{
			if (stats.st_mode & S_IXUSR)
			{
				free_tab(split_path);	
				return (abs_path);
			}
			else
			{
			    ft_printf_fd(2, "vsh: permission denied: %s\n", args[0]);
			    break;
			}
		}*/
		i++;
	}
	free_tab(split_path);
	free(abs_path);
	return (error(errnum % 2, args[0]);
}

char			*solve_cmd_path(char **args)
{
	if (args[0][0] == '/')
		return (solve_abs_path(args));
	else if (args[0][0] == '.')
	{
		if (ft_strcmp(args[0], ".") == 0)
		    return (sec(ft_strdup(".")));
		return (solve_relative_path(args));
	}
	else if (args[0][0] == '~')
		return (solve_home(args[0]));
	else
		return (find_path(args));	
}
