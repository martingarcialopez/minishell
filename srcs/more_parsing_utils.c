/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 11:44:45 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/02 11:44:47 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "tree.h"
#include "libft.h"

void				remove_whitespaces(t_list **alst)
{
	t_list	*lst;
	t_list	*tmp;
	t_token	*token;

	lst = *alst;
	while (lst)
	{
		token = (t_token*)lst->content;
		if (token->type == space)
		{
			tmp = lst->next;
			ft_lstdelone(alst, lst, &free_token);
			lst = tmp;
		}
		else
			lst = lst->next;
	}
}
