/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:01:45 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/02 09:21:59 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"

#define SINGLE_QUOTE 39
#define DOUBLE_QUOTE 34

static void		ssingle_quote(t_list **begin, t_list *lst,
						char *last, char *backsl)
{
	t_token	*token;

	token = (t_token*)((lst)->content);
	if (!*backsl && !*last)
	{
		*last = SINGLE_QUOTE;
		ft_lstdelone(begin, lst, &free_token);
	}
	else if (!*backsl && *last == SINGLE_QUOTE)
	{
		*last = 0;
		ft_lstdelone(begin, lst, &free_token);
	}
	else if (*backsl || *last == DOUBLE_QUOTE)
	{
		if (*backsl)
			*backsl = 0;
		token->type = literal;
	}
}

static void		ddouble_quote(t_list **begin, t_list *lst,
						char *last, char *backsl)
{
	t_token	*token;

	token = (t_token*)((lst)->content);
	if (!*backsl && !*last)
	{
		*last = DOUBLE_QUOTE;
		ft_lstdelone(begin, lst, &free_token);
	}
	else if (!*backsl && *last == DOUBLE_QUOTE)
	{
		*last = 0;
		ft_lstdelone(begin, lst, &free_token);
	}
	else if (*backsl || *last == SINGLE_QUOTE)
	{
		if (*backsl)
			*backsl = 0;
		token->type = literal;
	}
}

static void		bbackslash(t_list **begin, t_list *lst,
						char *last, char *backsl)
{
	t_token *token;

	token = (t_token*)(lst->content);
	if (!*backsl && (!*last || *last == DOUBLE_QUOTE))
	{
		*backsl = 1;
		ft_lstdelone(begin, lst, &free_token);
	}
	else if (*backsl || *last == SINGLE_QUOTE)
	{
		if (*backsl)
			*backsl = 0;
		token->type = literal;
	}
}

void			turn_token_to_literal(t_token **token, char last, char *backsl)
{
	if (!((*token)->type == variable && last == DOUBLE_QUOTE && !*backsl))
		(*token)->type = literal;
	if (*backsl)
		*backsl = 0;
}

void			solve_quotes(t_list **alst)
{
	t_list	*lst;
	t_list	*tmp;
	t_token	*token;
	char	last;
	char	backsl;

	lst = *alst;
	last = 0;
	backsl = 0;
	while (lst)
	{
		tmp = lst->next;
		token = (t_token*)(lst->content);
		if (token->type == single_quote)
			ssingle_quote(alst, lst, &last, &backsl);
		else if (token->type == double_quote)
			ddouble_quote(alst, lst, &last, &backsl);
		else if (token->type == backslash)
			bbackslash(alst, lst, &last, &backsl);
		else if (backsl || last)
			turn_token_to_literal(&token, last, &backsl);
		lst = tmp;
	}
	if (last)
		parse_error(2, &last, alst);
}
