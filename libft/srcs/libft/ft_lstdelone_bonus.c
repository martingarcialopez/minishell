/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 09:49:12 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/02 17:37:27 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		lst_null(t_list **lst)
{
	free(*lst);
	*lst = NULL;
}

void		ft_lstdelone(t_list **alst, t_list *lst, void (*del)(void *))
{
	t_list *prev;

	prev = *alst;
	if (prev == lst)
	{
		*alst = lst->next;
		(*del)(lst->content);
		lst_null(&lst);
		return ;
	}
	while (prev)
	{
		if (prev->next && prev->next == lst)
		{
			prev->next = lst->next;
			break ;
		}
		prev = prev->next;
	}
	if (lst)
	{
		(*del)(lst->content);
		lst_null(&lst);
	}
}
