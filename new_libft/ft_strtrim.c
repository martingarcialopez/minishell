/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:56:19 by daprovin          #+#    #+#             */
/*   Updated: 2019/11/10 17:37:26 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*trim;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (ft_isinstr(s1[i], set))
		i++;
	j = 0;
	if (i != len)
		while (ft_isinstr(s1[len - 1 - j], set))
			j++;
	if (!(trim = (char*)malloc(sizeof(char) * (len - i - j + 1))))
		return (NULL);
	len = len - i - j;
	j = 0;
	while (j < len)
		trim[j++] = s1[i++];
	trim[j] = 0;
	return (trim);
}
