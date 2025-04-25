/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:07:26 by dcampas-          #+#    #+#             */
/*   Updated: 2024/10/03 11:38:10 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	count_substr(char const *s, char c)
{
	int	count;
	int	insubstr;

	count = 0;
	insubstr = 0;
	while (*s)
	{
		if (*s != c && insubstr == 0)
		{
			insubstr = 1;
			count++;
		}
		else if (*s == c)
			insubstr = 0;
		s++;
	}
	return (count);
}

static int	word_lenth(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
	{
		len++;
	}
	return (len);
}

static char	**fill_result(char **result, const char *s, char c, int words)
{
	int	i;
	int	len;

	i = 0;
	while (*s && i < words)
	{
		if (*s != c)
		{
			len = word_lenth(s, c);
			result[i] = ft_substr(s, 0, len);
			if (!result[i])
				return (NULL);
			i++;
			s += len;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**result;

	words = count_substr(s, c);
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (fill_result(result, s, c, words));
}

/*
int main()
{
	char s[] = {"  H;ola    mundo me llamo     paco   "};
	char delim = ' ';
	int	i;
	char **result;

	i = 0;
	result = ft_split(s, delim);
	while (result[i])
	{
		printf("%s", result[i]);
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}*/
