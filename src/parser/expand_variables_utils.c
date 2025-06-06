/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:35:23 by dcampas-          #+#    #+#             */
/*   Updated: 2025/06/06 10:56:02 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Añadir un carácter al final de una cadena
char	*append_char(char *str, char c)
{
	char	*new;
	size_t	len;

	len = ft_strlen(str);
	new = malloc(len + 2);
	if (!new)
		return (NULL);
	ft_memcpy(new, str, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(str);
	return (new);
}

// Añadir una cadena al final de otra
char	*append_str(char *str, const char *to_append)
{
	char	*new;

	new = ft_strjoin(str, to_append);
	free(str);
	return (new);
}

// Actualiza el estado de la comillas
void	update_quote_state(char c, int *in_single_q, int *in_double_q)
{
	if (c == '\'' && !(*in_double_q))
		(*in_single_q) = !(*in_single_q);
	else if (c == '"' && !(*in_single_q))
		(*in_double_q) = !(*in_double_q);
}
