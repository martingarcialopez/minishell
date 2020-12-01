/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:53:10 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/01 12:55:37 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include <setjmp.h>
#include <sys/wait.h>
#include <signal.h>

void			new_prompt(void)
{
	ft_printf("(los voltereta)-> ");
}

void			split_lst_by_semicolon(t_list **alst, t_list **next)
{
	t_list		*lst;
	t_token		*ntoken;

	lst = *alst;
	*next = NULL;
	while (lst && lst->next)
	{
		ntoken = (t_token*)lst->next->content;
		if (ntoken->type == semicolon)
		{
			ft_lstdelone(alst, lst->next, &free_token);
			*next = lst->next;
			lst->next = NULL;
		}
		lst = (lst)->next;
	}
}

int				exec_single_command(char *line)
{
	solve_command(line);
	return (g_ret);
}

int				manage_flags(int ac, char **av, char **envp)
{
	if (ac >= 2 && ft_strcmp(av[1], "-c") == 0)
	{
		if (ac == 2)
		{
			ft_printf_fd(2, "%s: -c: option requires an argument\n",
								g_data[ARGV0]);
			exit(1);
		}
		while (--ac > 2)
			av[ac - 3] = av[ac];
		init_env(envp);
		init_data(av);
		return (exec_single_command(av[2]));
	}
	ft_printf_fd(2, "%s: %s: not a minishell option\n", g_data[ARGV0], av[1]);
	return (1);
}
