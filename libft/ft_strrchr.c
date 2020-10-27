/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:15:45 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/09 19:25:35 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		l;
	char	*p;

	l = ft_strlen(s);
	p = NULL;
	i = 0;
	while (i < l + 1)
	{
		if (s[i] == (char)c)
			p = (char*)s + i;
		i++;
	}
	return (p);
}
