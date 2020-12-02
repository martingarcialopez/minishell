/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:53:01 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/12/02 17:28:43 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list	arg;
	int		done;

	va_start(arg, format);
	done = ft_vprintf(1, format, arg);
	va_end(arg);
	return (done);
}

int		ft_printf_fd(int fd, const char *format, ...)
{
	va_list arg;
	int		done;

	va_start(arg, format);
	done = ft_vprintf(fd, format, arg);
	va_end(arg);
	return (done);
}
