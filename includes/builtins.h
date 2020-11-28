/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 11:05:39 by daprovin          #+#    #+#             */
/*   Updated: 2020/11/28 02:33:46 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

# define PWD 0
# define OLDPWD 1
# define ARGV0 2
# define ERROR_IDENTIFIER "%s: export: `%s': not a valid identifier\n"
# define ERROR_ASSIGNMENT "%s: bad assignment\n"
# define ERROR_NFOUND "%s: %s not found\n"

typedef struct			s_env
{
	char		*name;
	char		*value;
	int		stat;
	struct s_env	*next;
}				t_env;

typedef struct			s_bint_fnc
{
	char	*name;
	int	(*fnct)(char **);
}				t_bint_fnc;

char	*g_data[3];
t_env	*g_env;
int	g_ret;

int				ft_env(char **args);
int				init_env(char **envp);
int				ft_export(char **args);
int				ft_unset(char **args);
int				function(char **args);
int				ft_pwd(char **args);
int				ft_cd(char **args);
int				ft_echo(char **args);
int				ft_exit(char **args);
void			add_env(t_env  *new);
char			*join_value(char **data);
void			lst_free(t_env	*list);
void			list_rm_next(t_env *list);
void			save_return(int ret);
int				init_data(char **argv);
void			*sec(void *ptr);
void			new_env(char *name, char *value, int stat);
int				print_relative_path(char *home);
void			new_env_exp(char **data, int stat);
void			init_tmp(char ***tmp, int l[2]);

#endif
