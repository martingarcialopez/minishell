/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 20:10:42 by daprovin          #+#    #+#             */
/*   Updated: 2020/01/20 23:41:19 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_printchar(t_form *info, va_list args)
{
	int		just;
	char	c;

	c = va_arg(args, int);
	just = info->just - 1;
	if (!(info->flag & FLAG_MIN))
	{
		ft_doingjust(just, ' ');
		ft_putchar_fd(c, 1);
	}
	if (info->flag & FLAG_MIN)
	{
		ft_putchar_fd(c, 1);
		ft_doingjust(just, ' ');
	}
	if (info->just > 1)
		return (info->just);
	return (1);
}

static void	ft_printstring2(char *s, int l, t_form *info)
{
	int i;

	i = 0;
	while (i < l)
		ft_putchar_fd(s[i++], 1);
	ft_doingjust(info->just - l, ' ');
}

int			ft_printstring(t_form *info, va_list args)
{
	char	*s;
	char	n[7];
	int		l;
	int		i;

	ft_memcpy(n, "(null)", 6);
	s = va_arg(args, char*);
	s = (s == NULL) ? n : s;
	l = ft_strlen(s);
	l = (info->flag & FLAG_DOT && info->prec < l) ? info->prec : l;
	if (!(info->flag & FLAG_MIN))
	{
		ft_doingjust(info->just - l, ' ');
		i = 0;
		while (i < l)
			ft_putchar_fd(s[i++], 1);
	}
	if (info->flag & FLAG_MIN)
		ft_printstring2(s, l, info);
	if (info->just > l)
		return (info->just);
	return (l);
}

int			ft_printperc(t_form *info)
{
	if (info->flag & FLAG_MIN)
	{
		ft_putchar_fd('%', 1);
		ft_doingjust(info->just - 1, ' ');
	}
	else if (info->flag & FLAG_ZERO)
	{
		ft_doingjust(info->just - 1, '0');
		ft_putchar_fd('%', 1);
	}
	else
	{
		ft_doingjust(info->just - 1, ' ');
		ft_putchar_fd('%', 1);
	}
	if (info->just > 1)
		return (info->just);
	return (1);
}
