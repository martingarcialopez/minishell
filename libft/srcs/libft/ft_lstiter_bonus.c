/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:10:23 by mgarcia-          #+#    #+#             */
/*   Updated: 2019/10/14 10:14:26 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list **begin, t_list *lst, void (*f)(void *))
{
	*begin = (void*)begin;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
