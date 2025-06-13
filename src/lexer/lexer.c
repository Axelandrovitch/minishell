/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:45:49 by dcampas-          #+#    #+#             */
/*   Updated: 2025/06/09 16:37:09 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*handle_word_or_assignment(const char *line, int *i)
{
	char	buffer[1024];
	int		j;

	j = 0;
	while (line[*i] && !is_word_boundary(line[*i]))
	{
		if (line[*i] == '"' || line[*i] == '\'')
		{
			if (handle_quoted_char(line, i, buffer, &j) == -1)
				return (write(STDERR_FILENO, "minishell: Unclosed quote\n", 26),
					NULL);
		}
		else
		{
			if (j >= 1023)
				return (write(STDERR_FILENO, "Error: token too long\n", 22),
					NULL);
			buffer[j++] = line[(*i)++];
		}
	}
	buffer[j] = '\0';
	return (new_token(T_WORD, buffer, j));
}

static t_token	*handle_compound_word(const char *line, int *i)
{
	char	buffer[1024];
	int		j;

	j = 0;
	while (line[*i] && !is_word_boundary(line[*i]))
	{
		if (line[*i] == '"' || line[*i] == '\'')
		{
			if (handle_quoted_char(line, i, buffer, &j) == -1)
				return (write(STDERR_FILENO, "minishell: Unclosed quote\n", 26),
					NULL);
		}
		else
		{
			if (j >= 1023)
				return (write(STDERR_FILENO, "Error: token too long\n", 22),
					NULL);
			buffer[j++] = line[(*i)++];
		}
	}
	buffer[j] = '\0';
	if (j == 0)
		return (new_token(T_EMPTY, "", 0));
	return (new_token(T_WORD, buffer, j));
}

static t_token	*get_next_token(const char *line, int *i)
{
	if ((line[*i] == '"' || line[*i] == '\'')
		&& has_adjacent_content(line, *i, line[*i]))
		return (handle_compound_word(line, i));
	else if (line[*i] == '"')
		return (handle_quotes(line, i, '"'));
	else if (line[*i] == '\'')
		return (handle_quotes(line, i, '\''));
	else if (line[*i] == '|')
		return (handle_pipe(i));
	else if (line[*i] == '<' || line[*i] == '>')
		return (handle_redir(line, i));
	else
		return (handle_word_or_assignment(line, i));
}

static void	add_token_to_list(t_token **head, t_token **last, t_token *new_tok)
{
	if (!*head)
		*head = new_tok;
	else
		(*last)->next = new_tok;
	*last = new_tok;
}

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
		new_tok = get_next_token(line, &i);
		if (!new_tok)
			return (free_tokens(head), NULL);
		add_token_to_list(&head, &last, new_tok);
	}
	return (head);
}
