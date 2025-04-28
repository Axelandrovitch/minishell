/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:23:03 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/28 10:23:53 by marvin           ###   ########.fr       */
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
t_token		*new_token(t_token_type type, const char *value, int len)
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

void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("Type: %d | Value: \"%s\"\n", token->type, token->value);
		token = token->next;
	}
}