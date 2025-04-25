/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:26:23 by dcampas-          #+#    #+#             */
/*   Updated: 2024/10/03 13:08:45 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && (s1[i] == s2[i]) && (i < n - 1))
	{
		i++;
	}
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}
/*
int main()
{
	char s1[] = "HOLi";
	char s2[] = "HOLA";

	printf("%d", ft_strncmp(s1, s2, 4));
	return 0;
}*/
