/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:45:49 by dcampas-          #+#    #+#             */
/*   Updated: 2025/06/05 12:14:48 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*handle_word_or_assignment(const char *line, int *i)
{
	char	buffer[1024];
	int		j;

	j = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
	{
		if (line[*i] == '"' || line[*i] == '\'')
		{
			handle_quoted_char(line, i, buffer, &j);
		}
		else
			buffer[j++] = line[(*i)++];
		if (j >= 1024)
			return (fprintf(stderr, "Error: token demasiado largo\n"), NULL);
	}
	buffer[j] = '\0';
	return (new_token(T_WORD, buffer, j));
}

static t_token	*get_next_token(const char *line, int *i)
{
	if (line[*i] == '"')
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

// Tokenizes a line of input into a linked list of tokens
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
