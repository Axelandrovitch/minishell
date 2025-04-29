/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:23:03 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/29 12:40:11 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Skips spaces and tabs in the input
int	skip_spaces(const char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

// Creates a new token with the given type and value
t_token	*new_token(t_token_type type, const char *value, int len)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strndup(value, len);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->next = NULL;
	return (new_token);
}

// Frees the memory allocated for the tokens
void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
}

// Converts the token type to a string for debugging purposes !!!DELETE!!!
const char *token_type_to_string(t_token_type type)
{
	switch (type)
	{
		case T_WORD:		return ("T_WORD");
		case T_PIPE:		return ("T_PIPE");
		case T_REDIR_IN:	return ("T_REDIR_IN");
		case T_REDIR_OUT:	return ("T_REDIR_OUT");
		case T_REDIR_APPEND:return ("T_REDIR_APPEND");
		case T_HEREDOC:		return ("T_HEREDOC");
		case T_DQUOTE:		return ("T_DQUOTE");
		case T_SQUOTE:		return ("T_SQUOTE");
		case T_EMPTY:		return ("T_EMPTY");
		default:			return ("UNKNOWN");
	}
}



void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("Type: %s | %s \n", token_type_to_string(token->type), token->value);
		token = token->next;
	}
}
