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
//
// t_token	*create_quote_token(const char *line, int len, char quote_type)
// {
// 	if (len == 0)
// 		return (new_token(T_EMPTY, "", 0));
// 	if (quote_type == '"')
// 		return (new_token(T_DQUOTE, line, len));
// 	else
// 		return (new_token(T_SQUOTE, line, len));
// }
//
// t_token	*handle_pipe(int *i)
// {
// 	t_token	*token;
//
// 	token = new_token(T_PIPE, "|", 1);
// 	if (!token)
// 		return (NULL);
// 	(*i)++;
// 	return (token);
// }
//
// t_token	*handle_redir(const char *line, int *i)
// {
// 	t_token	*token;
//
// 	if (line[*i] == '<' && line[*i + 1] != '\0' && line[*i + 1] == '<')
// 	{
// 		token = new_token(T_HEREDOC, "<<", 2);
// 		(*i) += 2;
// 	}
// 	else if (line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>')
// 	{
// 		token = new_token(T_REDIR_APPEND, ">>", 2);
// 		(*i) += 2;
// 	}
// 	else if (line[*i] == '<')
// 	{
// 		token = new_token(T_REDIR_IN, "<", 1);
// 		(*i)++;
// 	}
// 	else if (line[*i] == '>')
// 	{
// 		token = new_token(T_REDIR_OUT, ">", 1);
// 		(*i)++;
// 	}
// 	else
// 		return (NULL);
// 	return (token);
// }
//
// int	handle_quoted_char(const char *line, int *i, char *buffer, int *j)
// {
// 	char	quote;
//
// 	quote = line[(*i)++];
// 	while (line[*i] && line[*i] != quote)
// 	{
// 		buffer[(*j)++] = line[(*i)++];
// 	}
// 	if (line[*i] == quote)
// 		(*i)++;
// 	return (0);
// }

t_token	*create_quote_token(const char *line, int len, char quote_type)
{
	if (len == 0)
		return (new_token(T_EMPTY, "", 0));
	if (quote_type == '"')
		return (new_token(T_DQUOTE, line, len));
	else
		return (new_token(T_SQUOTE, line, len));
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
	if (line[*i] == quote)
	{
		(*i)++;
		return (0);
	}
	while (line[*i] && line[*i] != quote)
	{
		if (*j >= 1023)
			return (-1);
		buffer[(*j)++] = line[(*i)++];
	}
	if (line[*i] == quote)
		(*i)++;
	else
		return (-1);
	return (0);
}
