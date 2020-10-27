/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing_types2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 23:22:50 by daprovin          #+#    #+#             */
/*   Updated: 2020/01/20 23:24:41 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printnoflag(int l, int n, int just, t_form *info)
{
	unsigned int x;

	x = n;
	ft_doingjust(just, ' ');
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		x = -1 * n;
	}
	ft_doingjust(info->prec - l, '0');
	if (l != 0 || x != 0)
		ft_putnbr_fd(x, 1);
}

static void	ft_printflagzero(int n, unsigned int x, int just)
{
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		x = -1 * n;
	}
	ft_doingjust(just, '0');
	ft_putnbr_fd(x, 1);
}

static void	ft_printint2(int l, t_form *info, int n)
{
	int				just;
	unsigned int	x;

	x = n;
	if (info->prec > l)
		just = info->just - info->prec;
	else
		just = info->just - l;
	if (info->flag & FLAG_MIN)
	{
		if (n < 0)
		{
			ft_putchar_fd('-', 1);
			x = -1 * n;
		}
		ft_doingjust(info->prec - l, '0');
		if (l != 0 || x != 0)
			ft_putnbr_fd(x, 1);
		ft_doingjust(just, ' ');
	}
	else if (info->flag & FLAG_ZERO)
		ft_printflagzero(n, x, just);
	else
		ft_printnoflag(l, n, just, info);
}

static int	ft_returnint(t_form *info, int l, int n)
{
	int r;

	r = l;
	if (info->prec > r)
		r = info->prec;
	if (info->just > r)
		r = info->just;
	if (n < 0)
		r++;
	return (r);
}

int			ft_printint(t_form *info, va_list args)
{
	int n;
	int aux;
	int l;

	n = va_arg(args, int);
	l = 1;
	aux = n / 10;
	while (aux != 0)
	{
		aux = aux / 10;
		l++;
	}
	if (info->flag & FLAG_DOT && n == 0 && info->prec == 0)
		l = 0;
	if (n < 0)
		(info->just)--;
	if (info->flag & FLAG_ZERO && info->flag & FLAG_DOT)
		info->flag &= (~FLAG_ZERO);
	ft_printint2(l, info, n);
	return (ft_returnint(info, l, n));
}
