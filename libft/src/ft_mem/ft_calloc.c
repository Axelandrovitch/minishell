/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:30:54 by dcampas-          #+#    #+#             */
/*   Updated: 2024/10/01 12:13:11 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
/*
int main()
{
    int *array;
    size_t count = 5;

    array = ft_calloc(count, sizeof(int));
    if (array == NULL)
    {
        printf("Error al asignar memoria\n");
        return 1; 
    }
    
	for (size_t i = 0; i < count; i++)
    {
        printf("array[%zu] = %d\n", i, array[i]); // Todos deberían ser 0
    }

    free(array);

    return 0;
}*/
