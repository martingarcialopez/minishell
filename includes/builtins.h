/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 11:05:39 by daprovin          #+#    #+#             */
/*   Updated: 2020/11/03 23:57:32 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

typedef struct			s_env
{
	char		*name;
	char		*value;
	struct s_env	*next;
}				t_env;

typedef struct			s_bint_fnc
{
	char	*name;
	int	(*fnct)(char **);
}				t_bint_fnc;

t_env	*g_env;

int				ft_env(char **args);
int				init_env(char **envp);
int				ft_export(char **args);
int				ft_unset(char **args);
int				function(char **args);
int				ft_pwd(char **args);
int				ft_cd(char **args);
int				ft_echo(char **args);
void				add_env(t_env  *new);
char				*join_value(char **data);
void				lst_free(t_env	*list);
void				list_rm_next(t_env *list);
void				save_return(int ret);

static t_bint_fnc	g_builtin_fnc[]=
{
	{"env", &ft_env},
	{"export", &ft_export},
	{"unset", &ft_unset},
	{"pwd", &ft_pwd},
	{"cd", &ft_cd},
	{"echo", &ft_echo},
	{NULL, 0}
};

#endif
