/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:16:59 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/28 11:35:42 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// char	*ft_strndup(const char *str, size_t n)
// {
// 	char	*dup;
//
// 	dup = malloc(n + 1);
// 	if (!dup)
// 		return (NULL);
// 	ft_strncpy(dup, str, n);
// 	dup[n] = '\0';
// 	return (dup);
// }

char	*ft_strndup(const char *str, size_t n)
{
	char	*dup;
	size_t	i;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

