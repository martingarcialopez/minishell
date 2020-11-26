/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:00:45 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/11/26 12:25:00 by mgarcia-         ###   ########.fr       */
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

void			signal_handler(int sigid)
{
	if (sigid == SIGINT)
	{
		ft_printf("\n");
		new_prompt();
	}
}

char			*get_input(void)
{
	char	*line;
	int		i;

	i = gnl(0, &line);
	if (!i)
	{
		ft_printf("exit\n");
		exit(0);
	}
	return (line);
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

void			print_token_lst(t_list *lst)
{
	t_token		*token;

	while (lst)
	{
		token = (t_token*)lst->content;
		printf("token: %d, value: %s\n", token->type, token->value);
		lst = lst->next;
	}
	ft_printf("\n");
}

void			solve_command(char *line)
{
	t_list	*token_lst;
	t_list	*next_lst;
	t_tree	*cmd_tree;
	int		ret;

		token_lst = pparse_line(line);
		while (token_lst)
		{
			//print_token_lst(token_lst);
			split_lst_by_semicolon(&token_lst, &next_lst);
			//expand_variables(&token_lst);
			cmd_tree = bbuild_tree(&token_lst);
			//print_ascii_tree(cmd_tree);
			ret = exec_commands(cmd_tree);
			save_return(ret);
			free_tree(cmd_tree);
			ft_lstclear(&token_lst, &free_token);
			token_lst = next_lst;
		}
}

void			prompt_loop(void)
{
	char	*line;

	while (1)
	{
		new_prompt();
		line = get_input();
		solve_command(line);
		free(line);
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

int				main(int ac, char **av, char **envp)
{
	if (ac > 1)
		return (manage_flags(ac, av, envp));
	init_env(envp);
	init_data(av);
	display_ascii_art();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	prompt_loop();
	return (0);
}
