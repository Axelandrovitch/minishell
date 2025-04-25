/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:50:07 by dcampas-          #+#    #+#             */
/*   Updated: 2024/10/03 12:52:18 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = (char)c;
	while (*s)
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (NULL);
}
/*
int main()
{
	char str[] = "laaaaaaaedrod";
	char target = 'd';
	char *pos;
	
	pos = ft_strchr(str, target);
	printf("Character '%c' found at position: %ld\n", target, pos - str);
	
	pos = 0;
	pos = strchr(str, target);
	printf("Character '%c' found at position: %ld\n", target, pos - str);
}*/
