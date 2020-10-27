/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 08:20:20 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/21 18:16:44 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *tmp_list;

	if (*lst && del)
	{
		while (*lst)
		{
			del((*lst)->content);
			tmp_list = *lst;
			*lst = (*lst)->next;
			free(tmp_list);
		}
		lst = NULL;
	}
}
