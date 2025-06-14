/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:23:03 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/29 17:22:54 by dcampas-         ###   ########.fr       */
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

	if (!value)
		return (NULL);
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
		if (token->value)
			free(token->value);
		free(token);
		token = tmp;
	}
}

// Counts the number of tokens in the linked list
int	count_tokens(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == T_WORD || tokens->type == T_DQUOTE
			|| tokens->type == T_SQUOTE || tokens->type == T_EMPTY)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

char	**get_args_from_tokens(t_token *tokens)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (count_tokens(tokens) + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (tokens->type == T_WORD || tokens->type == T_DQUOTE
			|| tokens->type == T_SQUOTE || tokens->type == T_EMPTY)
		{
			if (!process_single_token(tokens, args, i))
				return (free_vector(args), NULL);
			i++;
		}
		tokens = tokens->next;
	}
	args[i] = NULL;
	return (args);
}

/* char	**get_args_from_tokens(t_token *tokens)
{
	char	**args;
	int		i;
	char	*clean_value;

	args = malloc(sizeof(char *) * (count_tokens(tokens) + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (tokens->type == T_WORD)
		{
			args[i] = ft_strdup(tokens->value);
			if (!args[i++])
				return (free_vector(args), NULL);
		}
		else if (tokens->type == T_DQUOTE || tokens->type == T_SQUOTE)
		{
			clean_value = ft_strndup(tokens->value, ft_strlen(tokens->value));
			if (!clean_value)
				return (free_vector(args), NULL);
			args[i++] = clean_value;
		}
		else if (tokens->type == T_EMPTY)
		{
			args[i] = ft_strdup("");
			if (!args[i++])
				return (free_vector(args), NULL);
		}
		tokens = tokens->next;
	}
	args[i] = NULL;
	return (args);
}
 */