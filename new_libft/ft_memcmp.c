/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:32:11 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/17 18:52:20 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		dif;

	dif = 0;
	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	if (*(unsigned char*)s1 == 0 || *(unsigned char*)s2 == 0)
		return (*(unsigned char*)s1 - *(unsigned char*)s2);
	while (i < n)
	{
		if (*(unsigned char*)(s1 + i) != *(unsigned char*)(s2 + i))
			return (*(unsigned char*)(s1 + i) - *(unsigned char*)(s2 + i));
		i++;
	}
	return (dif);
}
