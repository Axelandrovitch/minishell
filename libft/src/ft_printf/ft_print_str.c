/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:02:35 by dcampas-          #+#    #+#             */
/*   Updated: 2024/10/10 12:24:46 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"
#include "../../inc/libft.h"

int	ft_print_str(va_list	args)
{
	char	*str;
	int		count;

	str = va_arg(args, char *);
	count = 0;
	if (str == NULL)
	{
		ft_putstr_printf("(null)");
		return (6);
	}
	while (*str)
	{
		ft_putchar_printf(*str);
		str++;
		count++;
	}
	return (count);
}
