/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:40:01 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/22 05:46:04 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp_lst;
	t_list	*f_lst;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	tmp_lst = lst;
	if (!(f_lst = ft_lstnew(f(tmp_lst->content))))
		return (NULL);
	tmp_lst = tmp_lst->next;
	while (tmp_lst)
	{
		if (!(tmp = ft_lstnew(f(tmp_lst->content))))
		{
			ft_lstclear(&f_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&f_lst, tmp);
		tmp_lst = tmp_lst->next;
	}
	return (f_lst);
}
