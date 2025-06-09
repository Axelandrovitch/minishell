/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahetru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:47:02 by ahetru            #+#    #+#             */
/*   Updated: 2025/06/09 17:47:08 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_word_boundary(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}

int	has_adjacent_content(const char *line, int i, char quote_type)
{
	int	temp_i;

	temp_i = i;
	if (line[temp_i] != quote_type)
		return (0);
	temp_i++;
	while (line[temp_i] && line[temp_i] != quote_type)
		temp_i++;
	if (line[temp_i] != quote_type)
		return (0);
	temp_i++;
	return (line[temp_i] && !is_word_boundary(line[temp_i]));
}
