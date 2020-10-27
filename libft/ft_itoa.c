/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:28:43 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/17 20:50:53 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int				i;
	int				l;
	unsigned int	sup;
	char			*s;

	l = ft_lengthnumb(n);
	s = (char*)ft_calloc(sizeof(char), l + 1);
	if (!s)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		sup = -1 * n;
	}
	else
		sup = n;
	i = 1;
	while (i <= l && s[l - i] != '-')
	{
		s[l - i] = sup % 10 + 48;
		sup = sup / 10;
		i++;
	}
	return (s);
}
