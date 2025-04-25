/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:37:13 by dcampas-          #+#    #+#             */
/*   Updated: 2024/09/24 19:34:27 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*cpy;

	len = ft_strlen(s);
	cpy = (char *)malloc((len + 1) * sizeof(char));
	if (cpy == NULL)
		return (NULL);
	ft_strlcpy(cpy, s, len + 1);
	return (cpy);
}
/*
int main()
{
    const char *original = "Hola, mundo!";
    char *duplicada;
    
    duplicada = ft_strdup(original);
    if (duplicada == NULL)
    {
        printf("Error al duplicar la cadena\n");
        return 1; // Salir si hubo un error
    }

    printf("Cadena original: %s\n", original);
    printf("Cadena duplicada: %s\n", duplicada);

    free(duplicada);

    return 0;
}*/
