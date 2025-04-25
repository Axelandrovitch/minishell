/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:13:27 by dcampas-          #+#    #+#             */
/*   Updated: 2025/01/10 15:29:22 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int		ft_putchar_printf(char c);
int		ft_putstr_printf(char	*s);
int		ft_putnbr_printf(int n);
int		ft_putnbr_base(unsigned long long n, const char *base);
int		ft_printf(char const *format, ...);
int		ft_print_char(va_list	args);
int		ft_print_str(va_list	args);
int		ft_print_int(int n);
int		ft_print_ptr(unsigned long long ptr);
int		ft_print_unsi(unsigned int n);
int		ft_print_hex(unsigned int n, int is_lower);
int		ft_print_perc(va_list	args);
#endif
