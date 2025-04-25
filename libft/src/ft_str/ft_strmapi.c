/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:37:08 by dcampas-          #+#    #+#             */
/*   Updated: 2024/10/01 11:55:28 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*newresult;
	int		i;

	if (!s)
		return (NULL);
	newresult = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!newresult)
		return (NULL);
	i = 0;
	while (s[i])
	{
		newresult[i] = f(i, s[i]);
		i++;
	}
	newresult[i] = '\0';
	return (newresult);
}
