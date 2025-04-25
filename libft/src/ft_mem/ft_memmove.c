/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:50:52 by dcampas-          #+#    #+#             */
/*   Updated: 2024/09/18 16:11:06 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (src == dest)
		return (dest);
	if (dest <= src)
	{
		while (i < n)
		{
			*((unsigned char *)dest + i) = *((const char *)src + i);
			i++;
		}
		return (dest);
	}
	else
	{
		while (n > 0)
		{
			*((unsigned char *)dest + n - 1) = *((const char *)src + n - 1);
			n--;
		}
		return (dest);
	}
	return (dest);
}
/*
int main()
{
	char dest[10];
	char src[] = "0123456789";
	
	ft_memmove(dest, src, 10);
	printf("%s", dest);
	return 0;
}*/
