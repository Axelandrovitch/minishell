/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:36:11 by dcampas-          #+#    #+#             */
/*   Updated: 2024/10/09 13:48:22 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"
#include "../../inc/libft.h"

int	ft_print_hex(unsigned int n, int is_lower)
{
	if (is_lower)
		return (ft_putnbr_base (n, "0123456789abcdef"));
	else
		return (ft_putnbr_base (n, "0123456789ABCDEF"));
}
