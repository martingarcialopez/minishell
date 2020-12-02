/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:01:01 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/02 16:57:03 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"

static void			swap_list_elements(t_list **link1, t_list **link2,
																t_list **alst)
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

void				set_a_b(int *redir, t_list **a, t_list **b, t_list **lst)
{
	if (!*redir)
		*a = (*lst)->next;
	else
		*b = (*lst)->next;
	*redir = 1;
}

void				redirection_party_trick(t_list **alst)
{
	t_list	*lst;
	t_list	*a;
	t_list	*b;
	t_token	*t;
	int		redir[3];

	ft_memset(redir, 0, 3 * sizeof(int));
	lst = *alst;
	a = NULL;
	b = NULL;
	while (lst)
	{
		t = (t_token*)lst->content;
		if (t->type == right_redir)
			set_a_b(&(redir[0]), &a, &b, &lst);
		else if (t->type == double_right_redir)
			set_a_b(&(redir[1]), &a, &b, &lst);
		else if (t->type == left_redir)
			set_a_b(&(redir[2]), &a, &b, &lst);
		if (t->type == semicolon)
			ft_memset(redir, 0, 3 * sizeof(int));
		lst = lst->next;
	}
	if (a && b)
		swap_list_elements(&a, &b, alst);
}
