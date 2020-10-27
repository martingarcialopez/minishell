/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:53:19 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/17 18:54:38 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pt;
	size_t	i;

	if (!(pt = (void*)malloc(size * count)))
		return (NULL);
	i = 0;
	while (i < size * count)
	{
		*(char*)(pt + i) = 0;
		i++;
	}
	return (pt);
}
