/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:55:41 by dcampas-          #+#    #+#             */
/*   Updated: 2024/09/17 16:22:09 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/*
int main()
{
	char ch = 'A';

    if (ft_isalpha(ch))
        printf("%c es una letra del alfabeto.\n", ch);
    else
        printf("%c no es una letra del alfabeto.\n", ch);

    return 0;
}*/
