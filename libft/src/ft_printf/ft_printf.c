/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:23:03 by dcampas-          #+#    #+#             */
/*   Updated: 2024/10/17 16:09:12 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"
#include "../../inc/libft.h"

int	ft_print_format(va_list	args, char type)
{
	if (type == 'c')
		return (ft_print_char(args));
	if (type == 's')
		return (ft_print_str(args));
	if (type == 'p')
		return (ft_print_ptr(va_arg(args, unsigned long long)));
	if (type == 'd' || type == 'i')
		return (ft_print_int(va_arg(args, int)));
	if (type == 'u')
		return (ft_print_unsi(va_arg(args, unsigned int)));
	if (type == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), 1));
	if (type == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), 0));
	if (type == '%')
		return (ft_putchar_printf('%'));
	return (ft_putchar_printf('%') + ft_putchar_printf(type));
}

int	ft_printf(char const	*format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	if (!format)
	{
		return (-1);
	}
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += ft_print_format(args, *format);
		}
		else
		{
			count += ft_putchar_printf(*format);
		}
		format++;
	}
	va_end(args);
	return (count);
}
