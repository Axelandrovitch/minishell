/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:49:06 by dcampas-          #+#    #+#             */
/*   Updated: 2025/01/10 15:49:08 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

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
	count += ft_putchar(base[n % base_len]);
	return (count);
}
