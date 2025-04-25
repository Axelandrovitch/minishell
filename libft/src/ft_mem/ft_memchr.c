/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:51:13 by dcampas-          #+#    #+#             */
/*   Updated: 2024/09/19 16:19:04 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}
/*
int main(void)
{	
	const char str[] = "Hola a todos";
	char target = 'd';
	char *result;

	result = (char *)ft_memchr(str, target, 10);

	if (result != NULL)
		printf("Caracter '%c' encontrado en la posición: %ld\n"
, target, result - str);
	else
		printf("Caracter '%c' no encontrado en los primeros 10 bytes.\n"
, target);

	return 0;
}*/
