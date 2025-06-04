/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:29:00 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/29 17:37:16 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// static t_token	*handle_quotes(const char *line, int *i, char quote_type)
// {
// 	int		start;
// 	int		len;
// 	t_token	*token;
//
// 	len = 0;
// 	(*i)++;
// 	start = *i;
// 	while (line[*i] && line[*i] != quote_type)
// 	{
// 		if (line[*i] == '\\' && line[*i + 1] != '\0'
// 			&& (line[*i + 1] == quote_type || line[*i + 1] == '\\'))
// 			(*i)++;
// 		(*i)++;
// 	}
// 	if (line[*i] != quote_type)
// 		return (fprintf(stderr, "Error: Unclosed quote\n"), NULL);
// 	len = *i - start;
// 	if (len == 0)
// 		token = new_token(T_EMPTY, "", 0);
// 	else
// 	{
// 		if (quote_type == '"')
// 			token = new_token(T_DQUOTE, line + start, len);
// 		else
// 			token = new_token(T_SQUOTE, line + start, len);
// 	}
// 	if (line[*i] == quote_type)
// 		(*i)++;
// 	return (token);
// }
//
static int	is_separator(char c)
{
	return (c == ' ' || c == '>' || c == '<' || c == '|');
}

static int	is_quote_type(char c, char type)
{
	return (c == type);
}

t_token	*create_quote_token(const char *line ,int len, char quote_type)
{
	if (len == 0)
		return (new_token(T_EMPTY, "", 0));
	if (quote_type == '"')
		return (new_token(T_DQUOTE, line, len));
	else
		return (new_token(T_SQUOTE, line, len));
}



t_token	*handle_quotes(const char *line, int *i, char quote_type)
{
	char	buffer[1024];
	t_token	*token;
	int		j;
	int		quote_count;

	j = 0;
	quote_count = 0;
	if (!line[(*i) + 1])
	{
		write(STDERR_FILENO, "Error: Unclosed quote\n", 22);
		return (NULL);

	}
	while (line[*i] && line[*i] != quote_type)
	{
		if (line[*i] == '\\' && line[*i + 1] != '\0'
			&& (line[*i + 1] == quote_type || line[*i + 1] == '\\'))
			(*i)++;
		buffer[j++] = line[(*i)++];
	}
	while (line[*i] && !is_separator(line[*i]))
	{
		if (line[*i] == '\\' && line[*i + 1] != '\0'
			&& (line[*i + 1] == quote_type || line[*i + 1] == '\\'))
			(*i)++;
		if (is_quote_type(line[*i], quote_type))
			quote_count++;
		if (!is_quote_type(line[*i], quote_type))
			buffer[j++] = line[(*i)];
		(*i)++;
	}
	buffer[j] = '\0';
	if (quote_count < 2)
	{
		write(STDERR_FILENO, "Error: Unclosed quote\n", 22);
		return (NULL);
	}
	token = (create_quote_token(buffer, j, quote_type));
	if (line[*i] == quote_type)
		(*i)++;
	return (token);
}

t_token	*handle_pipe(int *i)
{
	t_token	*token;

	token = new_token(T_PIPE, "|", 1);
	if (!token)
		return (NULL);
	(*i)++;
	return (token);
}

t_token	*handle_redir(const char *line, int *i)
{
	t_token	*token;

	if (line[*i] == '<' && line[*i + 1] != '\0' && line[*i + 1] == '<')
	{
		token = new_token(T_HEREDOC, "<<", 2);
		(*i) += 2;
	}
	else if (line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>')
	{
		token = new_token(T_REDIR_APPEND, ">>", 2);
		(*i) += 2;
	}
	else if (line[*i] == '<')
	{
		token = new_token(T_REDIR_IN, "<", 1);
		(*i)++;
	}
	else if (line[*i] == '>')
	{
		token = new_token(T_REDIR_OUT, ">", 1);
		(*i)++;
	}
	else
		return (NULL);
	return (token);
}

int	handle_quoted_char(const char *line, int *i, char *buffer, int *j)
{
	char	quote;

	quote = line[(*i)++];
	while (line[*i] && line[*i] != quote)
	{
		buffer[(*j)++] = line[(*i)++];
	}
	if (line[*i] == quote)
		(*i)++;
	return (0);
}
