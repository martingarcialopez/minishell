/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trambolic_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:54:32 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/02 16:57:00 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"

static void			put_lstnext_before_redir(int *redir, t_list **elem,
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

void				init_variables(t_list **lst, t_list **prev, int *redir,
																t_list **alst)
{
	*lst = *alst;
	*prev = NULL;
	*redir = 0;
}

void				trambolic_redirections(t_list **alst)
{
	t_list	*lst;
	t_list	*prev;
	t_token	*t;
	t_token	*nt;
	int		redir;

	init_variables(&lst, &prev, &redir, alst);
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
