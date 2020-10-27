/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:44:04 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/10 18:47:21 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		sig;
	long	n;

	i = 0;
	sig = 1;
	n = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sig = -1 * sig;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		n = 10 * n + (str[i++] - 48);
		if (n < 0 && sig == -1)
			return (0);
		if (n < 0 && sig == 1)
			return (-1);
	}
	return (sig * n);
}
