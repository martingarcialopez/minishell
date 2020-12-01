/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:01:12 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/01 13:46:31 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"

void				remove_whitespaces(t_list **alst)
{
	t_list	*lst;
	t_list	*tmp;
	t_token	*token;

	lst = *alst;
	while (lst)
	{
		token = (t_token*)lst->content;
		if (token->type == space)
		{
			tmp = lst->next;
			ft_lstdelone(alst, lst, &free_token);
			lst = tmp;
		}
		else
			lst = lst->next;
	}
}

void				join_dollar(t_list **alst)
{
	t_list	*lst;
	t_token	*tkn;
	t_token	*ntkn;
	char	*tmp;

	lst = *alst;
	while (lst && lst->next)
	{
		tkn = (t_token*)lst->content;
		ntkn = (t_token*)lst->next->content;
		if (tkn->type == literal && ntkn->type == variable)
		{
			tkn->type = variable;
			tmp = tkn->value;
			tkn->value = ft_strjoin(tkn->value, ntkn->value);
			free(tmp);
			ft_lstdelone(alst, lst->next, &free_token);
			continue ;
		}
		if ((tkn->type == variable && ntkn->type == literal)
			|| (tkn->type == variable && ntkn->type == variable))
		{
			tmp = tkn->value;
			tkn->value = ft_strjoin(tkn->value, ntkn->value);
			free(tmp);
			ft_lstdelone(alst, lst->next, &free_token);
			continue;
		}
		lst = lst->next;
	}
}

static int			is_operator(t_token_type type)
{
	if (type == pipeline || type == or || type == and
			|| type == left_redir)
		return (1);
	return (0);
}

void				check_syntax(t_list **alst)
{
	t_list	*lst;
	t_token *tkn;
	t_token *ntkn;

	lst = *alst;
	while (lst && lst->next)
	{
		tkn = (t_token*)lst->content;
		ntkn = (t_token*)lst->next->content;
		if ((is_operator(tkn->type) || tkn->type == semicolon) && lst == *alst)
		{
			parse_error(1, tkn->value, alst);
			return ;
		}
		else if ((tkn->type == right_redir || tkn->type == double_right_redir)
			&& ntkn->type != literal)
		{
			parse_error(1, tkn->value, alst);
			return ;
		}
		else if (is_operator(tkn->type) && ntkn->type != literal)
		{
			parse_error(1, tkn->value, alst);
			return ;
		}
		else if (tkn->type != literal && is_operator(ntkn->type))
		{
			parse_error(1, tkn->value, alst);
			return ;
		}
		if (lst)
			lst = lst->next;
	}
	if (lst)
	{
		tkn = (t_token*)lst->content;
		if (is_operator(tkn->type))
		{
			parse_error(1, tkn->value, alst);
			return ;
		}
	}
}
