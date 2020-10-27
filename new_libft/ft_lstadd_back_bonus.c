/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 06:19:09 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/18 07:00:26 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *list;

	list = *alst;
	if (!list)
	{
		*alst = new;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = new;
}
