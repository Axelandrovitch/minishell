/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahetru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:02:36 by ahetru            #+#    #+#             */
/*   Updated: 2025/06/06 12:02:37 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	extract_variables_from_braces(const char *input,
			int *pos, char *var)
{
	int	i;

	i = 0;
	while (input[*pos] && input[*pos] != '}' && i < 255)
		var[i++] = input[(*pos)++];
	if (input[*pos] == '}')
		(*pos)++;
	return (i);
}

static int	extract_variable(const char *input, int *pos, char *var)
{
	int	i;

	i = 0;
	while (input[*pos] && (ft_isalnum(input[*pos]) || input[*pos] == '_'))
		var[i++] = input[(*pos)++];
	return (i);
}

static char	*get_variable_value(t_shell *shell, const char *var)
{
	char	*tmp_value;
	char	*copy;

	tmp_value = ft_getenv(shell, var);
	if (tmp_value)
	{
		copy = ft_strdup(tmp_value);
		free(tmp_value);
		return (copy);
	}
	return (ft_strdup(""));
}

// Extraer y exandir la vble de entorno
char	*extract_and_expand(const char *input, int *pos, t_shell *shell)
{
	char	var[256];
	int		i;

	i = 0;
	(*pos)++;
	if (input[*pos] == '?')
	{
		(*pos)++;
		return (ft_itoa(shell->last_exit_status));
	}
	if (input[*pos] == '{')
	{
		(*pos)++;
		i = extract_variables_from_braces(input, pos, var);
	}
	else
		i = extract_variable(input, pos, var);
	var[i] = '\0';
	return (get_variable_value(shell, var));
}
