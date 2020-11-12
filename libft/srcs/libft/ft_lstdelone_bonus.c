/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 09:49:12 by mgarcia-          #+#    #+#             */
/*   Updated: 2019/10/18 18:25:54 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, t_list *lst, void (*del)(void *))
{
	t_list *prev;

	prev = *alst;
	if (prev == lst)
	{
		*alst = lst->next;
		return ;
	}
	while (prev)
	{
		if (prev->next && prev->next == lst)
		{
			prev->next = lst->next;
			break;
		}
		prev = prev->next;
	}
	if (lst)
	{
		(*del)(lst->content);
		free(lst);
		lst = NULL;
	}
}
