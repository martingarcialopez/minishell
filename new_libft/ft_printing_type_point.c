/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing_type_point.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 04:49:41 by daprovin          #+#    #+#             */
/*   Updated: 2020/01/20 23:24:57 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbrbase(long n, char *base)
{
	int		i;
	char	c;
	char	str[13];

	i = 0;
	if (n == 0)
		str[i++] = '0';
	while (n != 0)
	{
		str[i] = base[n % 16];
		n = n / 16;
		i++;
	}
	str[i] = '\0';
	i = 0;
	while (ft_strlen(str) / 2 - i > 0)
	{
		c = str[i];
		str[i] = str[ft_strlen(str) - i - 1];
		str[ft_strlen(str) - i - 1] = c;
		i++;
	}
	write(1, "0x", 2);
	ft_putstr_fd(str, 1);
}

static void	ft_printaddress(int l, t_form *info, long n)
{
	int just;

	just = info->just - l;
	if (info->flag & FLAG_MIN)
	{
		ft_putnbrbase(n, "0123456789abcdef");
		ft_doingjust(just, ' ');
	}
	else
	{
		ft_doingjust(just, ' ');
		ft_putnbrbase(n, "0123456789abcdef");
	}
}

static int	ft_returnadd(t_form *info, int l)
{
	int r;

	r = l;
	if (info->just > r)
		r = info->just;
	return (r);
}

int			ft_printadr(t_form *info, va_list args)
{
	long	n;
	long	aux;
	int		l;
	void	*p;

	p = va_arg(args, void *);
	n = (long)p;
	l = 1;
	aux = n / 16;
	while (aux != 0)
	{
		aux = aux / 16;
		l++;
	}
	l = l + 2;
	ft_printaddress(l, info, n);
	return (ft_returnadd(info, l));
}
