/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:19:37 by dcampas-          #+#    #+#             */
/*   Updated: 2024/09/19 16:42:42 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*temp1;
	unsigned char	*temp2;

	i = 0;
	temp1 = (unsigned char *)s1;
	temp2 = (unsigned char *)s2;
	while (n > i)
	{
		if (temp1[i] != temp2[i])
			return (temp1[i] - temp2[i]);
		i++;
	}
	return (0);
}
/*
int main(void)
{
    char s1[] = "abcdef";
    char s2[] = "abcdez";
    
    int result = ft_memcmp(s1, s2, 5);  // Comparar los primeros 5 bytes
    if (result == 0)
        printf("Las cadenas son iguales en los primeros 5 bytes.\n");
    else
        printf("Las cadenas son diferentes. Resultado: %d\n", result);

    return 0;
}*/
