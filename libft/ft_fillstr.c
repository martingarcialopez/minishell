/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:29:55 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/16 14:35:19 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_fillstr(char **split, char const *s, char c)
{
	int count;
	int i;
	int j;

	i = 0;
	count = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] != c && s[i] != 0)
			split[count][j++] = s[i++];
		if (j != 0)
		{
			count++;
			i--;
		}
		i++;
	}
}
