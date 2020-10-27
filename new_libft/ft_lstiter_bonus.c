/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:26:48 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/22 05:41:33 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *tmp_lst;

	tmp_lst = NULL;
	if (lst && f)
	{
		tmp_lst = lst;
		while (tmp_lst)
		{
			f(tmp_lst->content);
			tmp_lst = tmp_lst->next;
		}
	}
}
