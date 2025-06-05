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

static int	process_char(t_parse_state *state, char quote_type, int *in_quotes)

{
	if (state->line[state->i] == quote_type)
	{
		*in_quotes = !(*in_quotes);
		state->i++;
	}
	else
	{
		if (*in_quotes && should_escape(state->line, state->i, quote_type))
			state->i++;
		if (state->j >= 1023)
		{
			write(STDERR_FILENO, "minishell: Token too long\n", 26);
			return (-1);
		}
		state->buffer[state->j++] = state->line[state->i];
		state->i++;
	}
	return (0);
}

t_token	*handle_quotes(const char *line, int *i, char quote_type)
{
	t_parse_state	state;
	int				in_quotes;

	state.line = line;
	state.i = *i;
	state.j = 0;
	in_quotes = 0;
	while (state.line[state.i])
	{
		if (process_char(&state, quote_type, &in_quotes) == -1)
			return (NULL);
	}
	if (in_quotes)
	{
		write(STDERR_FILENO, "minishell: Unclosed quote\n", 26);
		return (NULL);
	}
	state.buffer[state.j] = '\0';
	*i = state.i;
	if (quote_type == '"')
		return (new_token(T_DQUOTE, state.buffer, state.j));
	return (new_token(T_SQUOTE, state.buffer, state.j));
}
