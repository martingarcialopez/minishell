/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:04:14 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/01 19:24:18 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"

static t_token		g_token_tab[] = {
	{"|", pipeline},
	{"<", left_redir},
	{">", right_redir},
	{";", semicolon},
	{"&", half_and},
	{"\'", single_quote},
	{"\"", double_quote},
	{"\\", backslash},
	{" ", space},
	{"$", variable},
	{">>", double_right_redir},
	{"&&", and},
	{"||", or},
	{0, 0}
};

t_list				*line_to_token_list(char *line)
{
	t_list	*begin;
	t_list	*lst;
	t_token	*token;
	char	str[2];
	int		i;

	begin = NULL;
	str[1] = '\0';
	while (*line)
	{
		token = (t_token*)sec(malloc(sizeof(t_token)));
		token->type = literal;
		str[0] = *line++;
		token->value = sec(ft_strdup(str));
		i = 0;
		while (g_token_tab[i].value)
		{
			if (ft_strcmp(g_token_tab[i].value, token->value) == 0)
				token->type = g_token_tab[i].type;
			i++;
		}
		lst = sec(ft_lstnew((void*)token));
		ft_lstadd_back(&begin, lst);
	}
	return (begin);
}

void				join_token_of_the_same_type(t_list **alst)
{
	t_list	**begin;
	t_list	*lst;
	t_token	*token;
	t_token	*next_token;
	char	*tmp;

	begin = alst;
	lst = *alst;
	while (lst && lst->next)
	{
		token = (t_token*)(lst->content);
		next_token = (t_token*)(lst->next->content);
		if (token->type == next_token->type)
		{
			tmp = token->value;
			token->value = sec(ft_strjoin(token->value, next_token->value));
			free(tmp);
			ft_lstdelone(begin, lst->next, &free_token);
		}
		else
			lst = lst->next;
	}
}

void				do_the_reevaluation_thing(t_list **lst, t_token **token,
														int *i, t_list **alst)
{
	*i = 0;
	while (g_token_tab[*i].value)
	{
		if (ft_strcmp(g_token_tab[*i].value, (*token)->value) == 0)
		{
			(*token)->type = g_token_tab[*i].type;
			if ((*token)->type == half_and)
			{
				parse_error(1, (*token)->value, alst);
				*lst = NULL;
			}
			break ;
		}
		(*i)++;
	}
}

static void			reevaluate_token(t_list **alst)
{
	t_list	*lst;
	t_token	*token;
	int		i;

	lst = *alst;
	while (lst)
	{
		token = (t_token*)(lst->content);
		if (token->type != literal && token->type != space)
		{
			do_the_reevaluation_thing(&lst, &token, &i, alst);
			if (!g_token_tab[i].value)
			{
				parse_error(1, token->value, alst);
				lst = NULL;
				return ;
			}
		}
		if (lst)
			lst = lst->next;
	}
}

t_list				*pparse_line(char *line)
{
	t_list	*lst;

	lst = line_to_token_list(line);
	solve_quotes(&lst);
	join_token_of_the_same_type(&lst);
	reevaluate_token(&lst);
	join_dollar(&lst);
	remove_whitespaces(&lst);
	trambolic_redirections(&lst);
	redirection_party_trick(&lst);
	the_strange_case_of_misterious_redirection_combinations(&lst);
	check_syntax(&lst);
	return (lst);
}
