/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:00:45 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/02 18:08:38 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"
#include <signal.h>

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

void			solve_command(char *line)
{
	t_list	*token_lst;
	t_list	*next_lst;
	t_tree	*cmd_tree;
	int		ret;
	char	sep;

	if ((token_lst = pparse_line(line)) == NULL)
		return (save_return(SYNTAX_ERROR));
	while (token_lst)
	{
		split_lst_by_semicolon(&token_lst, &next_lst, &sep);
		expand_variables(&token_lst);
		cmd_tree = bbuild_tree(token_lst);
		ret = exec_commands(cmd_tree);
		save_return(ret);
		free_tree(cmd_tree);
		ft_lstclear(&token_lst, &free_token);
		token_lst = next_lst;
		if ((sep == 'a' && g_ret != 0) || (sep == 'o' && g_ret == 0))
		{
			if (token_lst)
				ft_lstclear(&token_lst, &free_token);
			break ;
		}
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
