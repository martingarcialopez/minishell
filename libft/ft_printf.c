/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 21:01:17 by daprovin          #+#    #+#             */
/*   Updated: 2020/01/20 23:40:10 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_makevalues2(const char *format, t_form *info, va_list args)
{
	while (ft_isnotthetype(*format) && ft_isnothing(*format))
	{
		if (*format == '*' && *(format - 1) != '.')
			info->just = va_arg(args, int);
		if (*format == '*' && *(format - 1) == '.')
			info->prec = va_arg(args, int);
		if (*format == '.' && ft_isdigit(*(format + 1)))
			info->prec = ft_atoi(format + 1);
		if (ft_isdigit(*format) && *(format - 1) != '.'
			&& !(ft_isdigit(*(format - 1))))
			info->just = ft_atoi(format);
		format++;
	}
	if (info->just < 0)
	{
		info->flag |= FLAG_MIN;
		info->just *= -1;
	}
}

static void	ft_makevalues(const char *format, t_form *info, va_list args)
{
	int dot;

	info->just = 0;
	info->prec = 0;
	dot = 0;
	if (info->flag & FLAG_STAR)
		ft_makevalues2(format, info, args);
	else
		while (ft_isnotthetype(*format) && ft_isnothing(*format))
		{
			if (*format == '.')
				dot = 1;
			if (ft_isdigit(*format))
			{
				if (dot == 0)
					info->just = ft_atoi(format);
				else if (dot == 1)
					info->prec = ft_atoi(format);
				while (ft_isdigit(*format))
					format++;
				format--;
			}
			format++;
		}
}

static int	ft_makeinfo(const char *format, t_form *info, va_list args)
{
	int i;

	i = 0;
	while (ft_isnotthetype(*format) && ft_isnothing(*format))
	{
		if (*format == '-')
			info->flag |= FLAG_MIN;
		else if (*format == '0' && !(ft_isdigit(*(format - 1)))
			&& *(format - 1) != '.')
			info->flag |= FLAG_ZERO;
		else if (*format == '.')
			info->flag |= FLAG_DOT;
		else if (*format == '*')
			info->flag |= FLAG_STAR;
		format++;
		i++;
	}
	info->type = *format;
	i = (!(ft_isnotthetype(*format))) ? i + 1 : i;
	ft_makevalues(format - i + 1, info, args);
	if (info->prec < 0)
		info->flag &= (~FLAG_DOT);
	return (i);
}

static int	ft_printtype(t_form *info, va_list args)
{
	int i;

	i = 0;
	if (info->type == 'c')
		i = ft_printchar(info, args);
	else if (info->type == 's')
		i = ft_printstring(info, args);
	else if (info->type == 'p')
		i = ft_printadr(info, args);
	else if ((info->type == 'd') || (info->type == 'i'))
		i = ft_printint(info, args);
	else if (info->type == 'u')
		i = ft_printuint(info, args);
	else if (info->type == 'x' || info->type == 'X')
		i = ft_printhex(info, args);
	else if (info->type == '%')
		i = ft_printperc(info);
	return (i);
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	t_form	info;

	va_start(args, format);
	i = 0;
	while (*format)
	{
		if (*format == '%')
		{
			info.flag = 0;
			format++;
			format = format + ft_makeinfo(format, &info, args);
			i += ft_printtype(&info, args);
		}
		if (*format != '%' && *format != '\0')
		{
			ft_putchar_fd(*format, 1);
			if (*format)
				ft_suport(&i, &format);
		}
	}
	va_end(args);
	return (i);
}
