/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 09:57:28 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/01 09:57:30 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "tree.h"

void	init_tmp(char ***tmp, int l[2])
{
	t_env	*lst;

	l[0] = 0;
	l[1] = 0;
	lst = g_env;
	while (lst != NULL)
	{
		lst = lst->next;
		l[0]++;
	}
	*tmp = (char **)sec(malloc(sizeof(char *) * l[0]));
	while (l[1] < l[0])
		(*tmp)[l[1]++] = NULL;
	l[1] = 0;
}
