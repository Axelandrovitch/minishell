/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:35:23 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/29 12:44:33 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Añadir un carácter al final de una cadena
static char	*append_char(char *str, char c)
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
static char	*append_str(char *str, const char *to_append)
{
	char	*new;

	new = ft_strjoin(str, to_append);
	free(str);
	return (new);
}

// Extraer y exandir la vble de entorno
static char	*extract_and_expand(const char *input, int *pos)
{
	char	var[256];
	int		i;

	i = 0;
	(*pos)++;
	while (input[*pos] && (ft_isalnum(input[*pos]) || input[*pos] == '_'))
	{
		var[i++] = input[*pos];
		(*pos)++;
	}
	var[i] = '\0';
	if (getenv(var))
		return (ft_strdup(getenv(var)));
	return (ft_strdup(""));
}

// Actualiza el estado de la comillas
static void	update_quote_state(char c, int *in_single_q, int *in_double_q)
{
	if (c == '\'' && !(*in_double_q))
		(*in_single_q) = !(*in_single_q);
	else if (c == '"' && !(*in_single_q))
		(*in_double_q) = !(*in_double_q);
}

// Expande variables de entorno como $USER o $HOME
char	*expand_variables(const char *input)
{
	char	*result;
	char	*expanded_var;
	int		i;
	int		in_single_q;
	int		in_double_q;

	result = ft_strdup("");
	i = 0;
	in_single_q = 0;
	in_double_q = 0;
	if (!result)
		return (NULL);
	while (input[i])
	{
		// Si encontramos una comilla, actualizamos el estado
		if (input[i] == '\'' || input[i] == '\"')
		{
			update_quote_state(input[i], &in_single_q, &in_double_q);
			result = append_char(result, input[i++]);
		}
		// Si encontramos un $ y no estamos en comillas simples
		else if (input[i] == '$' && !in_single_q && input[i + 1]
				&& (ft_isalpha(input[i + 1]) || input[i + 1] == '_'))
		{
			expanded_var = extract_and_expand(input, &i);
			result = append_str(result, expanded_var);
			free(expanded_var);
		}
		else
		{
			result = append_char(result, input[i++]);
		}
	}
	return (result);
}

