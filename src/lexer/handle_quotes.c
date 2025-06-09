/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahetru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:45:31 by ahetru            #+#    #+#             */
/*   Updated: 2025/06/05 12:45:34 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	should_escape(const char *line, int i, char quote_type)
{
	if (line[i] != '\\' || line[i + 1] == '\0')
		return (0);
	if (quote_type == '"')
	{
		if (line[i + 1] == '"' || line[i + 1] == '\\')
			return (1);
	}
	if (quote_type == '\'' && line[i + 1] == '\'')
		return (1);
	return (0);
}

static int	process_quoted_content(t_parse_state *state, char quote_type)
{
	while (state->line[state->i] && state->line[state->i] != quote_type)
	{
		if (should_escape(state->line, state->i, quote_type))
			state->i++;
		if (state->j >= 1023)
		{
			write(STDERR_FILENO, "minishell: Token too long\n", 26);
			return (-1);
		}
		state->buffer[state->j++] = state->line[state->i++];
	}
	return (0);
}

static int	handle_empty_quotes(const char *line, int *i, char quote_type)
{
	if (line[*i] == quote_type && line[*i + 1] == quote_type)
	{
		if (line[*i + 2] && line[*i + 2] != ' ' && line[*i + 2] != '\t'
			&& line[*i + 2] != '|'
			&& line[*i + 2] != '<' && line[*i + 2] != '>')
			return (0);
		*i += 2;
		return (1);
	}
	return (0);
}

t_token	*handle_quotes(const char *line, int *i, char quote_type)
{
	t_parse_state	state;

	if (handle_empty_quotes(line, i, quote_type))
		return (new_token(T_EMPTY, "", 0));
	state.line = line;
	state.i = *i + 1;
	state.j = 0;
	if (process_quoted_content(&state, quote_type) == -1)
		return (NULL);
	if (state.line[state.i] != quote_type)
	{
		write(STDERR_FILENO, "minishell: Unclosed quote\n", 26);
		return (NULL);
	}
	state.i++;
	state.buffer[state.j] = '\0';
	*i = state.i;
	if (quote_type == '"')
		return (new_token(T_DQUOTE, state.buffer, state.j));
	return (new_token(T_SQUOTE, state.buffer, state.j));
}
