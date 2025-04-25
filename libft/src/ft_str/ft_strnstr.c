/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:43:22 by dcampas-          #+#    #+#             */
/*   Updated: 2024/09/19 17:21:49 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)(big));
	while (big[i] && i < len)
	{
		j = 0;
		while (big [i + j] != '\0' && little [j] && (i + j) < len
			&& big[i + j] == little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
    const char big[] = "Hello, world!";
    const char little[] = "orld";
    
    char *result = ft_strnstr(big, little, 13); 
    
    if (result)
        printf("Encontrado: %s\n", result);
    else
        printf("No encontrado.\n");

    return 0;
}*/
