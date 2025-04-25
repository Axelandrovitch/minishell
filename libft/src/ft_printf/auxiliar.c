/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:55:31 by dcampas-          #+#    #+#             */
/*   Updated: 2024/10/17 16:08:15 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"
#include "../../inc/libft.h"

int	ft_putchar_printf(char c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_putstr_printf(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		count += ft_putchar_printf(*s);
		s++;
	}
	return (count);
}

int	ft_putnbr_printf(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count += ft_putstr_printf("-2147483648");
		return (count);
	}
	if (n < 0)
	{
		count += ft_putchar_printf('-');
		n = -n;
	}
	if (n >= 10)
	{
		count += ft_putnbr_printf(n / 10);
	}
	count += ft_putchar_printf((n % 10) + '0');
	return (count);
}

int	ft_putnbr_base(unsigned long long n, const char *base)
{
	unsigned long long	base_len;
	int					count;

	base_len = ft_strlen(base);
	count = 0;
	if (base_len < 2)
		return (0);
	if (n >= base_len)
	{
		count += ft_putnbr_base(n / base_len, base);
	}
	count += ft_putchar_printf(base[n % base_len]);
	return (count);
}
