/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing_type_hex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 19:03:30 by daprovin          #+#    #+#             */
/*   Updated: 2020/01/20 23:24:20 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbrbase(unsigned int n, char *base)
{
	int		i;
	char	c;
	char	str[12];

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
	ft_putstr_fd(str, 1);
}

static void	ft_printhex2(int l, t_form *info, unsigned int n)
{
	int just;

	if (info->prec > l)
		just = info->just - info->prec;
	else
		just = info->just - l;
	if (info->flag & FLAG_MIN)
	{
		ft_doingjust(info->prec - l, '0');
		if (l != 0 || n != 0)
			ft_putnbrbase(n, "0123456789abcdef");
		ft_doingjust(just, ' ');
	}
	else if (info->flag & FLAG_ZERO)
	{
		ft_doingjust(just, '0');
		ft_putnbrbase(n, "0123456789abcdef");
	}
	else
	{
		ft_doingjust(just, ' ');
		ft_doingjust(info->prec - l, '0');
		if (l != 0 || n != 0)
			ft_putnbrbase(n, "0123456789abcdef");
	}
}

static void	ft_printcaphex(int l, t_form *info, unsigned int n)
{
	int just;

	if (info->prec > l)
		just = info->just - info->prec;
	else
		just = info->just - l;
	if (info->flag & FLAG_MIN)
	{
		ft_doingjust(info->prec - l, '0');
		if (l != 0 || n != 0)
			ft_putnbrbase(n, "0123456789ABCDEF");
		ft_doingjust(just, ' ');
	}
	else if (info->flag & FLAG_ZERO)
	{
		ft_doingjust(just, '0');
		ft_putnbrbase(n, "0123456789ABCDEF");
	}
	else
	{
		ft_doingjust(just, ' ');
		ft_doingjust(info->prec - l, '0');
		if (l != 0 || n != 0)
			ft_putnbrbase(n, "0123456789ABCDEF");
	}
}

static int	ft_returnhex(t_form *info, int l)
{
	int r;

	r = l;
	if (info->prec > r)
		r = info->prec;
	if (info->just > r)
		r = info->just;
	return (r);
}

int			ft_printhex(t_form *info, va_list args)
{
	unsigned int	n;
	unsigned int	aux;
	int				l;

	n = va_arg(args, unsigned int);
	l = 1;
	aux = n / 16;
	while (aux != 0)
	{
		aux = aux / 16;
		l++;
	}
	if (info->flag & FLAG_DOT && n == 0 && info->prec == 0)
		l = 0;
	if (info->flag & FLAG_ZERO && info->flag & FLAG_DOT)
		info->flag &= (~FLAG_ZERO);
	if (info->type == 'x')
		ft_printhex2(l, info, n);
	else
		ft_printcaphex(l, info, n);
	return (ft_returnhex(info, l));
}
