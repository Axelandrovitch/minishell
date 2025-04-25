/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:04:14 by dcampas-          #+#    #+#             */
/*   Updated: 2024/10/01 16:10:43 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	getlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*handle_min_int(void)
{
	char	*str;

	str = malloc(12);
	if (!str)
		return (NULL);
	ft_strlcpy(str, "-2147483648", 12);
	return (str);
}

char	*ft_itoa(int n)
{
	int		lenght;
	char	*str;

	if (n == -2147483648)
		return (handle_min_int());
	lenght = getlen(n);
	str = malloc (lenght + 1);
	if (!str)
		return (NULL);
	str[lenght] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[--lenght] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
/*
int main() {
    int numbers[] = {0, 42, -42, 2147483647, -2147483648};
    for (int i = 0; i < 5; i++) {
        char *result = ft_itoa(numbers[i]);
        if (result) {
            printf("El número %d como cadena es: |%s|\n", numbers[i], result);
            free(result); // Liberar memoria
        }
    }
    return 0;
}*/
