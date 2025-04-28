/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:40:07 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/26 14:14:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main()
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		input = readline("minishell> ");

		if (!input)
		{
			printf ("exit\n");
			break ;
		}
		if (input && *input)
			add_history(input);
		
		tokens = tokenize(input);
		print_tokens(tokens);
		if (!tokens)
		{
			printf("Error: Tokenization failed\n");
			free(input);
			continue;
		}
		free(input);
	}
	return (0);
}