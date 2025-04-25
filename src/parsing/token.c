/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:29:00 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/25 14:21:57 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*handle_quotes(const char *line, int *i, char quote_type)
{

}

static t_token	*handle_pipe(int *i)
{

}

static t_token	*handle_redir(const char *line, int *i)
{

}

static t_token	*handle_word(const char *line, int *i)
{

}

t_token			*tokenize(const char *line)
{
	t_token	*head;
	t_token	*last;
	t_token	*new_tok;
	int		i = 0;

	while (line[i])
	{
		i = skip_spaces(line, i);
		if (line[i] == '\0')
			break ;
		new_tok = NULL;
		if (line[i] == '"')
			new_tok = handle_quotes(line, &i, '"');

		else if (line[i] == '\'')
			new_tok = handle_quotes(line, &i, '"');
		
		else if (line[i] == '|')
			new_tok = handle_pipe(&i);
		
		else if (line[i] == '<' || line[i] == '>')
			new_tok = handle_redir(line, &i);

		else
			handle_word()

		
	}
}
