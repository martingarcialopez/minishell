/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:01:12 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/02 11:44:38 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"

static void			join_next_token(t_token **tkn, t_token *ntkn,
											t_list *lst, t_list **alst)
{
	char	*tmp;

	tmp = (*tkn)->value;
	(*tkn)->value = ft_strjoin((*tkn)->value, ntkn->value);
	free(tmp);
	ft_lstdelone(alst, lst->next, &free_token);
}

void				join_dollar(t_list **alst)
{
	t_list	*lst;
	t_token	*tkn;
	t_token	*ntkn;

	lst = *alst;
	while (lst && lst->next)
	{
		tkn = (t_token*)lst->content;
		ntkn = (t_token*)lst->next->content;
		if (tkn->type == literal && ntkn->type == variable)
		{
			tkn->type = variable;
			join_next_token(&tkn, ntkn, lst, alst);
			continue ;
		}
		if ((tkn->type == variable && ntkn->type == literal)
			|| (tkn->type == variable && ntkn->type == variable))
		{
			join_next_token(&tkn, ntkn, lst, alst);
			continue;
		}
		lst = lst->next;
	}
}

static int			is_operator(t_token_type type)
{
	if (type == pipeline || type == or || type == and)
		return (1);
	return (0);
}

static void			check_first_or_last_element(t_list *lst, t_list **alst)
{
	t_token *tkn;

	if (lst)
	{
		tkn = (t_token*)lst->content;
		if (is_operator(tkn->type) || (tkn->type == semicolon && lst == *alst))
			return (parse_error(1, tkn->value, alst));
	}
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
			return (parse_error(1, tkn->value, alst));
		else if ((tkn->type == right_redir || tkn->type == double_right_redir
				|| tkn->type == left_redir) && ntkn->type != literal)
			return (parse_error(1, tkn->value, alst));
		else if (is_operator(tkn->type) && ntkn->type != literal)
			return (parse_error(1, tkn->value, alst));
		else if (tkn->type != literal && is_operator(ntkn->type))
			return (parse_error(1, tkn->value, alst));
		if (lst)
			lst = lst->next;
	}
	check_first_or_last_element(lst, alst);
}
