/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:01:01 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/11/25 19:42:10 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"

static void	put_lstnext_before_redir(int *redir, t_list **elem,
		t_list **prev, t_list **begin)
{
	t_list	*elem_prev;
	t_list	*elem_next;
	t_list	*prev_next;

	*redir = 0;
	elem_prev = *elem;
	*elem = (*elem)->next;
	elem_next = (*elem)->next;
	if (*prev == NULL)
	{
		(*elem)->next = *begin;
		*begin = *elem;
	}
	else
	{
		prev_next = (*prev)->next;
		(*prev)->next = *elem;
		(*elem)->next = prev_next;
	}
	elem_prev->next = elem_next;
}

static void	swap_list_elements(t_list **link1, t_list **link2, t_list **alst)
{
	t_list	*lst;
	t_list	*l1_prev;
	t_list	*l2_prev;
	t_list	*swap;

	lst = *alst;
	while (lst)
	{
		if (lst->next == *link1)
			l1_prev = lst;
		else if (lst->next == *link2)
			l2_prev = lst;
		lst = lst->next;
	}
	swap = (*link1)->next;
	(*link1)->next = (*link2)->next;
	(*link2)->next = swap;
	l1_prev->next = *link2;
	l2_prev->next = *link1;
}

void		trambolic_redirections(t_list **alst)
{
	t_list	*lst;
	t_list	*prev;
	t_token	*t;
	t_token	*nt;
	int		redir;

	lst = *alst;
	prev = NULL;
	redir = 0;
	while (lst && lst->next)
	{
		t = (t_token*)lst->content;
		nt = (t_token*)lst->next->content;
		if (t->type == right_redir || t->type == double_right_redir)
			redir = 1;
		else if (t->type == semicolon)
			redir = 0;
		else if (nt->type == right_redir || nt->type == double_right_redir)
			prev = lst;
		else if (redir && t->type == literal && nt->type == literal)
		{
			put_lstnext_before_redir(&redir, &lst, &prev, alst);
			lst = *alst;
			continue ;
		}
		lst = lst->next;
	}
}

void		redirection_party_trick(t_list **alst)
{
	t_list	*lst;
	t_list	*a;
	t_list	*b;
	t_token	*t;
	int		redir;

	lst = *alst;
	redir = 0;
	a = NULL;
	b = NULL;
	while (lst)
	{
		t = (t_token*)lst->content;
		if (t->type == right_redir || t->type == double_right_redir)
		{
			a = !redir ? lst->next : a;
			b = redir ? lst->next : b;
			redir++;
		}
		lst = lst->next;
	}
	if (a && b)
		swap_list_elements(&a, &b, alst);
}
