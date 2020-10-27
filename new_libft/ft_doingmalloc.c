/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doingmalloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:48:46 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/22 05:41:06 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_doingmalloc(char **split, char const *s, char c)
{
	int		i;
	int		j;
	int		count;

	i = -1;
	count = 0;
	while (s[++i])
	{
		j = i;
		while (s[i] != c && s[i] != 0)
			i++;
		if (j != i)
		{
			if (!(split[count] = (char*)malloc(sizeof(char) * (i - j + 1))))
			{
				ft_doingfree(split, count);
				return (1);
			}
			split[count][i - j] = 0;
			count++;
			i--;
		}
	}
	return (0);
}
