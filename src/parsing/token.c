/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:29:00 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/29 13:09:42 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*handle_quotes(const char *line, int *i, char quote_type)
{
	int		start;
	int		len;
	t_token	*token;

	len = 0;
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote_type)
	{
		if (line[*i] == '\\' && line[*i + 1] != '\0'
			&& (line[*i + 1] == quote_type || line[*i + 1] == '\\'))
		{
			(*i)++;
		}
		(*i)++;
	}
	if (line[*i] != quote_type)
		perror("Error: Unclosed quote\n");
	len = *i - start;
	if (len == 0)
		token = new_token(T_EMPTY, "", 0);
	else
	{
		if (quote_type == '"')
			token = new_token(T_DQUOTE, line + start, len);
		else
			token = new_token(T_SQUOTE, line + start, len);
	}
	if (!token)
		return (NULL);
	if (line[*i] == quote_type)
		(*i)++;
	return (token);
}

static t_token	*handle_pipe(int *i)
{
	t_token	*token;

	token = new_token(T_PIPE, "|", 1);
	if (!token)
		return (NULL);
	(*i)++;
	return (token);
}

// Handles redirection tokens (<<, >>, <, >)
static t_token	*handle_redir(const char *line, int *i)
{
	t_token	*token;

	//no se salga de los límites de la cadena
	if (line[*i] == '\0')
		return (NULL);
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

// Handles word tokens (words, commands, etc.)
static t_token	*handle_word(const char *line, int *i)
{
	int	len;
	int	start;

	start = *i;
	len = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && line[*i] != '|'
		&& line[*i] != '<' && line[*i] != '>' && line[*i] != '"' && line[*i] != '\'')
	{
		(*i)++;
		len++;
	}
	return (new_token(T_WORD, line + start, len));
}

// Tokenizes the input line into a linked list of tokens
// Returns the head of the linked list
t_token	*tokenize(const char *line)
{
	t_token	*head;
	t_token	*last;
	t_token	*new_tok;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (line[i])
	{
		i = skip_spaces(line, i);
		if (line[i] == '\0')
			break ;
		if (line[i] == '"')
			new_tok = handle_quotes(line, &i, '"');
		else if (line[i] == '\'')
			new_tok = handle_quotes(line, &i, '\'');
		else if (line[i] == '|')
			new_tok = handle_pipe(&i);
		else if (line[i] == '<' || line[i] == '>')
			new_tok = handle_redir(line, &i);
		else
			new_tok = handle_word(line, &i);
		if (!new_tok)
			return (free_tokens(head), NULL);
		if (!head)
			head = new_tok;
		else
			last->next = new_tok;
		last = new_tok;
	}
	return (head);
}
