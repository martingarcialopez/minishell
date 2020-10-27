/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doingfree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:59:01 by daprovin          #+#    #+#             */
/*   Updated: 2019/10/16 15:02:02 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_doingfree(char **split, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
